#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    frameW = 320;
    frameH = 240;
    vid.initGrabber(frameW,frameH);
    nFrames = 0;
}

//--------------------------------------------------------------
void testApp::update(){ 
    vid.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    for (int i = 0; i < nFrames; i ++) {
        txs[i]->draw(i* (frameW/2 + 5), frameH, frameW/2, frameH/2);
    }
    vid.draw(0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case ' ':
            captureFrame();
            break;
        case 's':
            ofxGifEncoder::save(pxs, "test.gif", 256);
            break;
        default:
            break;
    }
}

void testApp::captureFrame() {
    unsigned char * temp = new unsigned char[frameW * frameH * 3];
    memcpy(temp, vid.getPixels(), frameW * frameH * 3);
    ofxGifFrame * gifFrame   = ofxGifEncoder::createGifFrame(temp, frameW, frameH, 0.1f) ;
    pxs.push_back(gifFrame);
    
    ofTexture * tx = new ofTexture();
    tx->allocate(frameW, frameH, GL_RGB);
    tx->loadData(gifFrame->pixels, gifFrame->width , gifFrame->height, GL_RGB);
    txs.push_back(tx);
    
    nFrames++;
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

