#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void onGifSaved(string & fileName);
        void exit();
        void captureFrame();
    
        vector <ofTexture *> txs; // for previewing
        vector <ofxGifFrame *> pxs;
        
        int frameW, frameH;
        int nFrames;
        
        ofVideoGrabber vid;
        ofxGifEncoder gifEncoder;

};
