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

// similar to ofPixels
typedef struct {
	unsigned char * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
} ofxGifFrame;

// make an ofxGifThreadedSaver?
class ofxGifEncoder: public ofThread {
    public:     
        
        ofxGifEncoder();
        ~ofxGifEncoder();
    
        void setup(int _w, int _h, int _nColors = 256, float _frameDuration = .1f);
        
        // thread saving
        // blocking, verbose
        void start() {startThread(true, false);}
        void stop() {stopThread();}
        void exit();
    
        void addFrame(ofImage & image, float duration = 0.1f, int bitsPerPixel = 24);        
        void addFrame(unsigned char * px, int _w, int _h, float duration = 0.1f, int bitsPerPixel = 24);

//    void addFrame();
        static ofxGifFrame * createGifFrame(unsigned char * px, int _w, int _h, float duration = 0.1f, int bitsPerPixel = 24);
        void save(string _fileName = "test.gif" );
    private:   
        void swapRgb(ofxGifFrame * pix);
        void threadedFunction();
        void update();
        void doSave();
        bool bSaving;

        vector <ofxGifFrame *> frames;
        string  fileName;
        int     nColors;
        float   frameDuration;
        int w;
        int h;
};

