//
//  ofxGifEncoder.h
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
// http://github.com/jesusgollonet/ofxGifEncoder
// adapted threaded saving, events, error checking and frame managing from Nick Hardeman.
// http://github.com/NickHardeman/ofxGifEncoder/tree/threaded
// Thanks!

#include "ofMain.h"
#include "FreeImage.h"
#include "ofxGifFrame.h"
#include "ofxGifDitherTypes.h"

#pragma once

class ofxGifEncoder: public ofThread {
    public:     
        
        ofxGifEncoder();
        ~ofxGifEncoder();
    
        void setup(int _w, int _h, float _frameDuration = 0.1f, int _nColors = 256 );
        void setNumColors(int _nColors = 256);
        void setDitherMode(int _ditherMode = OFX_GIF_DITHER_FS);
        void setFrameDuration(float _duration); // for all gifs;
        
        static ofEvent<string>	OFX_GIF_SAVE_FINISHED;

        // thread saving
        // blocking, verbose
        void start() {startThread(true, false);}
        void stop() {stopThread();}
        void exit();
		void reset();
        
        // if no duration is specified, we'll use default (from setup())
        void addFrame(ofImage & image, float duration = 0.f);        
        void addFrame(unsigned char * px, int _w, int _h, int _bitsPerPixel = 24, float duration = 0.f);

        static ofxGifFrame * createGifFrame(unsigned char * px, int _w, int _h, int _bitsPerPixel = 24, float duration = 0.1f);
        void save(string _fileName = "test.gif" );
    private:
        void calculatePalette(FIBITMAP * bmp);
        int getClosestToGreenScreenPaletteColorIndex();
        ofColor greenScreenColor;
        vector <ofColor> palette;
        ofxGifFrame * convertTo24BitsWithGreenScreen(ofxGifFrame * frame);
        void processFrame(ofxGifFrame * frame, FIMULTIBITMAP * multi);
        void swapRgb(ofxGifFrame * pix);
        void threadedFunction();
        void doSave();
        bool bSaving;

        vector <ofxGifFrame *> frames;
        string  fileName;
        int     nColors;
        float   frameDuration;
        int w;
        int h;
        int bitsPerPixel;
        int nChannels;
        int ditherMode;
    
    
};

