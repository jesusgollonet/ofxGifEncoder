/*
 *  ofxGifFrame.h
 */


#ifndef OFXGIFFR
#define OFXGIFFR

#include "ofMain.h"

class ofxGifFrame {
	
public:  
	
	ofxGifFrame(){
		pixels = NULL;
	};
	~ofxGifFrame(){
		if(pixels) delete[] pixels;		
	}
	
	unsigned char   * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
	
	
};
#endif