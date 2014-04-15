//
//  ofxGifFrame.h
//  ofxGifEncoderDev
//
//  Created by jesus gollonet on 4/15/14.
//
//

#pragma once

typedef struct {
	unsigned char * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
} ofxGifFrame;


