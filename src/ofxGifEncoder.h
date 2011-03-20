//
//  ofxGifEncoder.h
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "ofMain.h"


// similar to ofPixels
typedef struct {
	unsigned char * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
} ofxGifFrame;


class ofxGifEncoder {
    
    public: 
        static ofxGifFrame * createGifFrame(unsigned char * px, int _w, int _h, float duration = 0.1f, int bitsPerPixel = 24);
        static void save(vector <ofxGifFrame *> frames, string fileName = "test.gif" , int nColors = 256);
    private:
        static void swapRgb(ofxGifFrame * pix);
    
};