//
//  ofxGifEncoder.cpp
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.

#include "ofxGifEncoder.h"

// for some reason we're not seeing this from freeimage
#define DWORD uint32_t


ofEvent<string>	ofxGifEncoder::OFX_GIF_SAVE_FINISHED;

ofxGifEncoder::ofxGifEncoder() {
}

void ofxGifEncoder::setup(int _w, int _h,  float _frameDuration, int _nColors){
    if (_nColors < 2 || _nColors > 256) {
        ofLog(OF_LOG_WARNING, "ofxGifEncoder: nColors must be between 2 and 256. set to 256");
        nColors = 256;
    }
    w       = _w;
    h       = _h;
    
    frameDuration   = _frameDuration;
    nColors         = _nColors;
    bitsPerPixel    = 0;
    nChannels       = 0;
    ditherMode      = OFX_GIF_DITHER_NONE;
    bSaving         = false;
}

ofxGifEncoder::~ofxGifEncoder() {}


//--------------------------------------------------------------
ofxGifFrame * ofxGifEncoder::createGifFrame(unsigned char * px, int _w, int _h, int _bitsPerPixel, float _duration ) {
    ofxGifFrame * gf    = new ofxGifFrame();
    gf->pixels          = px;
    gf->width           = _w; 
    gf->height          = _h;
    gf->duration        = _duration;
    gf->bitsPerPixel    = _bitsPerPixel;
    return gf;
}

void ofxGifEncoder::addFrame(ofImage & img, float _duration) {

    if(img.width != w || img.height != h) {
        ofLog(OF_LOG_WARNING, "ofxGifEncoder::addFrame image dimensions don't match, skipping frame");
        return;
    }
    
    addFrame(img.getPixels(), w, h, img.bpp,  _duration);
}

void ofxGifEncoder::addFrame(unsigned char *px, int _w, int _h, int _bitsPerPixel, float _duration) {
    if(_w != w || _h != h) {
        ofLog(OF_LOG_WARNING, "ofxGifEncoder::addFrame image dimensions don't match, skipping frame");
        return;
    }
    
    float tempDuration = _duration;
    if (tempDuration == 0.f) tempDuration = frameDuration; 
    
    nChannels = 0;
    switch (_bitsPerPixel) {
        case 8:     nChannels = 1;      break;
        case 24:    nChannels = 3;      break;
        case 32:    nChannels = 4;      break;
        default:             
            ofLog(OF_LOG_WARNING, "bitsPerPixel should be 8, 24 or 32. skipping frame");
            return;
            break;
    }
    
    unsigned char * temp = new unsigned char[w * h * nChannels];
    memcpy(temp, px, w * h * nChannels);
    ofxGifFrame * gifFrame   = ofxGifEncoder::createGifFrame(temp, w, h, _bitsPerPixel, tempDuration) ;
    frames.push_back(gifFrame);
}

void ofxGifEncoder::setNumColors(int _nColors){
    nColors = _nColors;
}

void ofxGifEncoder::setDitherMode(int _ditherMode){
    ditherMode = _ditherMode;
}

void ofxGifEncoder::setFrameDuration(float _duration){
    for (int i = 0; i < frames.size(); i++) {
        frames[i]->duration = _duration;
    }
}



//--------------------------------------------------------------
void ofxGifEncoder::save (string _fileName) {
    if(bSaving) {
        ofLog(OF_LOG_WARNING, "ofxGifEncoder is already saving. wait for OFX_GIF_SAVE_FINISHED");
        return;
    }
    bSaving = true;
    fileName = _fileName;
    if(!isThreadRunning()) start();
}


//--------------------------------------------------------------
void ofxGifEncoder::threadedFunction() {
	while( isThreadRunning() != 0 ) {
		if( lock() ){
            
            if(bSaving) {
                doSave();
                bSaving = false;
                ofNotifyEvent(OFX_GIF_SAVE_FINISHED, fileName, this);
            }

			unlock();
			ofSleepMillis(10);
		}
	}
}

void ofxGifEncoder::doSave() {
	// create a multipage bitmap
	FIMULTIBITMAP *multi = FreeImage_OpenMultiBitmap(FIF_GIF, ofToDataPath(fileName).c_str(), TRUE, FALSE); 
	FIBITMAP * bmp = NULL;
	
	for(int i = 0; i < frames.size(); i++ ) { 
		// we need to swap the channels if we're on little endian (see ofImage::swapRgb);
#ifdef TARGET_LITTLE_ENDIAN
        swapRgb(frames[i]);
#endif
		// get the pixel data
		bmp	= FreeImage_ConvertFromRawBits(
            frames[i]->pixels, 
            frames[i]->width,
            frames[i]->height, 
            frames[i]->width*(frames[i]->bitsPerPixel/8), 
            frames[i]->bitsPerPixel, 
            0, 0, 0, true // in of006 this (topdown) had to be false.
        );	 
        
#ifdef TARGET_LITTLE_ENDIAN
        swapRgb(frames[i]);
#endif
        
        DWORD frameDuration = (DWORD) (frames[i]->duration * 1000.f);

        bmp = FreeImage_ColorQuantizeEx(bmp, FIQ_NNQUANT, nColors);
		
		// dithering :)
        if(ditherMode > OFX_GIF_DITHER_NONE) bmp = FreeImage_Dither(bmp, (FREE_IMAGE_DITHER)ditherMode);
        
		// clear any animation metadata used by this dib as we’ll adding our own ones 
		FreeImage_SetMetadata(FIMD_ANIMATION, bmp, NULL, NULL); 
		// add animation tags to dib[i] 
		FITAG *tag = FreeImage_CreateTag(); 
		
		if(tag) { 
			FreeImage_SetTagKey(tag, "FrameTime"); 
			FreeImage_SetTagType(tag, FIDT_LONG); 
			FreeImage_SetTagCount(tag, 1); 
			FreeImage_SetTagLength(tag, 4); 
			FreeImage_SetTagValue(tag, &frameDuration); 
			FreeImage_SetMetadata(FIMD_ANIMATION, bmp, FreeImage_GetTagKey(tag), tag); 
			FreeImage_DeleteTag(tag); 
		} 
		FreeImage_AppendPage(multi, bmp); 
	} 
	
	FreeImage_Unload(bmp);
	FreeImage_CloseMultiBitmap(multi); 
}
 
// from ofimage
//----------------------------------------------------
void ofxGifEncoder::swapRgb(ofxGifFrame * pix){
	if (pix->bitsPerPixel != 8){
		int sizePixels		= pix->width * pix->height;
		int cnt				= 0;
		unsigned char temp;
		int byteCount		= pix->bitsPerPixel/8;
        
		while (cnt < sizePixels){
			temp                            = pix->pixels[cnt*byteCount];
			pix->pixels[cnt*byteCount]		= pix->pixels[cnt*byteCount+2];
			pix->pixels[cnt*byteCount+2]	= temp;
			cnt++;
		}
	}
}

void ofxGifEncoder::exit() {
    stop();
}