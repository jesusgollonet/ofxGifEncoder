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

// similar to ofPixels
typedef struct {
	unsigned char * pixels;
    int width;
    int height;
    float duration;  // seconds
	int bitsPerPixel;
} ofxGifFrame;

// done for consistency. feel free to use Freeimage versions
enum ditherTypes {
    OFX_GIF_DITHER_NONE         = -1,
    OFX_GIF_DITHER_FS           = FID_FS,           // Floyd & Steinberg error diffusion
    OFX_GIF_DITHER_BAYER4x4     = FID_BAYER4x4,		// Bayer ordered dispersed dot dithering (order 2 dithering matrix)
    OFX_GIF_DITHER_BAYER8x8     = FID_BAYER8x8, 	// Bayer ordered dispersed dot dithering (order 3 dithering matrix)
    OFX_GIF_DITHER_CLUSTER6x6   = FID_CLUSTER6x6,	// Ordered clustered dot dithering (order 3 - 6x6 matrix)
    OFX_GIF_DITHER_CLUSTER8x8   = FID_CLUSTER8x8,	// Ordered clustered dot dithering (order 4 - 8x8 matrix)
    OFX_GIF_DITHER_CLUSTER16x16 = FID_CLUSTER16x16, // Ordered clustered dot dithering (order 8 - 16x16 matrix)
    OFX_GIF_DITHER_BAYER16x16   = FID_BAYER16x16,	// Bayer ordered dispersed dot dithering (order 4 dithering matrix)
};


// make an ofxGifThreadedSaver?
class ofxGifEncoder: public ofThread {
    public:     
        
        ofxGifEncoder();
        ~ofxGifEncoder();
    
        void setup(int _w, int _h, float _frameDuration = 0.1f, int _nColors = 256 );
        void setNumColors(int _nColors = 256);
        void setDitherMode(int _ditherMode = OFX_GIF_DITHER_FS);
        
        static ofEvent<string>	OFX_GIF_SAVE_FINISHED;

        // thread saving
        // blocking, verbose
        void start() {startThread(true, false);}
        void stop() {stopThread();}
        void exit();
        
        // if no duration is specified, we'll use default (from setup())
        void addFrame(ofImage & image, float duration = 0.f);        
        void addFrame(unsigned char * px, int _w, int _h, float duration = 0.f);

        static ofxGifFrame * createGifFrame(unsigned char * px, int _w, int _h, float duration = 0.1f, int _bitsPerPixel = 24);
        void save(string _fileName = "test.gif" );
    private:   
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
        int ditherMode;
    
    
};

