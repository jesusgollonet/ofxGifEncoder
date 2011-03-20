//
//  ofxGifEncoder.h
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "ofMain.h"




class ofxGifEncoder {
    
    public: 
        static void save(vector <ofPixels *> frames, string fileName);
    private:
        static void swapRgb(ofPixels * pix, int width, int height, int bitsPerPixel);
    
};