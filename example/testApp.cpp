#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    frameW = 100;
    frameH = 100;
    vid.initGrabber(frameW,frameH);
    nFrames = 0;
	ofBackground(50, 40, 50);
    
    gifEncoder.setup(frameW, frameH, .1f, 256);
    
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);

    transpGif.loadImage("abcde.gif");
    transpPng.loadImage("abcde.png");
    transpGif.setImageType(OF_IMAGE_GRAYSCALE);
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
    ofEnableAlphaBlending();
	transpGif.draw(0,0);
    transpPng.draw(100, 0);
    ofDisableAlphaBlending();
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW+10, 20);

}

void testApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case ' ':
            //captureFrame();
            gifEncoder.addFrame(transpGif);
            gifEncoder.save("t.gif");
            transpGif.saveImage("fake.gif");
            break;
        case 's':
            gifEncoder.save("test.gif");
            break;
        default:
            break;
    }
}

void testApp::captureFrame() {
    gifEncoder.addFrame(vid.getPixels(), frameW, frameH, 3);
    
    ofTexture * tx = new ofTexture();
    tx->allocate(frameW, frameH, GL_RGB);
    tx->loadData(vid.getPixels(), frameW, frameH, GL_RGB);
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
//--------------------------------------------------------------
void testApp::exit(){ 
    gifEncoder.exit();
}

