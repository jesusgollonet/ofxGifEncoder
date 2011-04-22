//
//  ofxGifEncoder.cpp
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxGifEncoder.h"
// for some reason we're not seeing this from freeimage
#define DWORD uint32_t

ofxGifEncoder* ofxGifEncoder::__instance = NULL;

ofEvent<int>		ofxGifEncoder::OFX_GIF_ENCODER_EVENT_START;
ofEvent<string>		ofxGifEncoder::OFX_GIF_ENCODER_EVENT_END;

//--------------------------------------------------------------
ofxGifEncoder::ofxGifEncoder() {
	_bNeedsSave		= false;
}

ofxGifEncoder::~ofxGifEncoder() {
	
}

//--------------------------------------------------------------
ofxGifEncoder* ofxGifEncoder::getInstance() {
	if (__instance == NULL) {
		__instance = new ofxGifEncoder();
		__instance->start();
	}
	return __instance;
}

//--------------------------------------------------------------
void ofxGifEncoder::addRGBFrame(unsigned char * px, int _w, int _h, float duration, int bitsPerPixel) {
	getInstance();
	
	unsigned char * temp = new unsigned char[_w * _h * 3];
    memcpy(temp, px, _w * _h * 3);
    __instance->_gifFrames.push_back( createGifFrame(temp, _w, _h, 0.1f, bitsPerPixel) );
}

//--------------------------------------------------------------
void ofxGifEncoder::addRGBFrame(ofImage& image, float duration, int bitsPerPixel) {
	if(image.type != OF_IMAGE_COLOR) {
		ofLog(OF_LOG_ERROR, "ofxGifEncoder :: addRGBFrame : image must be of type OF_IMAGE_COLOR");
	}
	addRGBFrame(image.getPixels(), image.width, image.height, duration, bitsPerPixel);
}

//--------------------------------------------------------------
ofxGifFrame * ofxGifEncoder::createGifFrame(unsigned char * px, int _w, int _h, float duration, int bitsPerPixel) {
    ofxGifFrame * gf    = new ofxGifFrame();
    gf->pixels          = px;
    gf->width           = _w; 
    gf->height          = _h; 
    gf->duration        = duration;
    gf->bitsPerPixel    = bitsPerPixel;
    return gf;
}

//--------------------------------------------------------------
void ofxGifEncoder::save(vector <ofxGifFrame *> frames, string fileName, int nColors) {
	getInstance();
    
    if (nColors < 2 || nColors > 256) {
        ofLog(OF_LOG_WARNING, "nColors must be between 2 and 256. your gif won't be saved");
        return;
    }
    clear();
	__instance->_gifFrames.swap(frames);
	//copy(frames.begin(), frames.end(), __instance->_gifFrames.begin()); 
	
	save(fileName, nColors);
}

//--------------------------------------------------------------
void ofxGifEncoder::save(string fileName, int nColors) {
	getInstance();
	
	cout << "calling the save function" << endl;
	
	if (nColors < 2 || nColors > 256) {
        ofLog(OF_LOG_WARNING, "nColors must be between 2 and 256. your gif won't be saved");
        return;
    }
	
	__instance->_fileName	= fileName;
	__instance->_nColors	= nColors;
	__instance->_bNeedsSave	= true;
	
}

//--------------------------------------------------------------
void ofxGifEncoder::threadedFunction() {
	while( isThreadRunning() != 0 ) {
		if( lock() ){
			update();
			unlock();
			ofSleepMillis(10);
		}
	}
}

//--------------------------------------------------------------
void ofxGifEncoder::update() {
	if(__instance->_bNeedsSave) {
		int temp = 1;
		ofNotifyEvent(OFX_GIF_ENCODER_EVENT_START, temp, this);
		__instance->_saveGIF();
		__instance->_bNeedsSave		= false;
		ofNotifyEvent(OFX_GIF_ENCODER_EVENT_END, __instance->_fileName, this);
	}
}

//----------------------------------------------------
void ofxGifEncoder::_saveGIF() {
	cout << "now saving the _saveGIF()" << endl;
	// create a multipage bitmap
	FIMULTIBITMAP *multi = FreeImage_OpenMultiBitmap(FIF_GIF, ofToDataPath(__instance->_fileName).c_str(), TRUE, FALSE); 
	
	FIBITMAP * bmp = NULL;
	
	for(int i = 0; i < __instance->_gifFrames.size(); i++ ) { 
		// we need to swap the channels if we're on little endian (see ofImage::swapRgb);
#ifdef TARGET_LITTLE_ENDIAN
        swapRgb(__instance->_gifFrames[i]);
#endif
		
		// get the pixel data
		bmp	= FreeImage_ConvertFromRawBits(
										   __instance->_gifFrames[i]->pixels, 
										   __instance->_gifFrames[i]->width,
										   __instance->_gifFrames[i]->height, 
										   __instance->_gifFrames[i]->width*(__instance->_gifFrames[i]->bitsPerPixel/8), 
										   __instance->_gifFrames[i]->bitsPerPixel, 
										   0,
										   0,
										   0, 
										   true // in of006 this (topdown) had to be false.
										   );	 
		
		
#ifdef TARGET_LITTLE_ENDIAN
        swapRgb(__instance->_gifFrames[i]);
#endif
		
        DWORD frameDuration = (DWORD) __instance->_gifFrames[i]->duration * 1000.f;
		
        // bmp =  FreeImage_ColorQuantize(bmp, FIQ_NNQUANT);
		
		// if we want to set a reduced color palette (2 to 256);
        bmp = FreeImage_ColorQuantizeEx(bmp, FIQ_NNQUANT, _nColors);
		
		// dithering :)
		// you can set a different dither pattern for each frame
        // bmp = FreeImage_Dither(bmp, (FREE_IMAGE_DITHER)((i+1)%6));
        //bmp = FreeImage_Dither(bmp, FID_BAYER8x8);
        
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

//----------------------------------------------------
void ofxGifEncoder::clear() {
	for (int i = 0; i < __instance->_gifFrames.size(); i++) {
		delete __instance->_gifFrames[i]->pixels;
		delete __instance->_gifFrames[i];
		__instance->_gifFrames[i] = NULL;
	}
	__instance->_gifFrames.clear();
	__instance->_bNeedsSave = false;
}

//----------------------------------------------------
void ofxGifEncoder::exit() {
	if(__instance != NULL) {
		clear();
		__instance->unlock();
		__instance->stopThread( true );
	}
}




