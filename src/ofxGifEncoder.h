//
//  ofxGifEncoder.h
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "ofMain.h"
#include "FreeImage.h"

// similar to ofPixels
typedef struct {
	unsigned char * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
} ofxGifFrame;


class ofxGifEncoder : public ofThread {

public: 
	static ofEvent<int>		OFX_GIF_ENCODER_EVENT_START;
	static ofEvent<string>	OFX_GIF_ENCODER_EVENT_END;
	
	ofxGifEncoder();
	~ofxGifEncoder();
	// thought it might be nice to have a singleton to save the frames. //
	static ofxGifEncoder* getInstance();
	static void addRGBFrame(unsigned char * px, int _w, int _h, float duration, int bitsPerPixel=24);
	static void addRGBFrame(ofImage& image, float duration, int bitsPerPixel=24);
	
	// thread saving //
	// blocking, verbose
	void start() {startThread(true, false);}
	void stop() {stopThread();}
	
	static ofxGifFrame * createGifFrame(unsigned char * px, int _w, int _h, float duration = 0.1f, int bitsPerPixel = 24);
	static void save(vector <ofxGifFrame *> frames, string fileName = "test.gif" , int nColors = 256);
	static void save(string fileName, int nColors);
	
	static void clear();
	static void exit();
private:
	static void swapRgb(ofxGifFrame* pix);
	void _saveGIF();
	
	void threadedFunction();
	void update();
	
	string	_fileName;
	int		_nColors;
	
	int		_saveFrameIndex;
	bool	_bAllFramesAdded;
	bool	_bNeedsSave;
	
	static ofxGifEncoder* __instance;
	vector <ofxGifFrame *> _gifFrames;
    
	static bool	_verbose;
};



