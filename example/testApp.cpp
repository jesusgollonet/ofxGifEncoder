#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    frameW  = 320;
    frameH  = 240;
    nFrames = 0;
    
    vid.initGrabber(frameW,frameH);

    gifEncoder.setup(frameW, frameH, .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
    
    ofBackground(50, 40, 50);
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
            captureFrame();
            break;
        case 's':
            cout <<"start saving\n" << endl;
            gifEncoder.save("test.gif");
            break;
        default:
            break;
    }
}

void testApp::captureFrame() {
    gifEncoder.addFrame(vid.getPixels(), frameW, frameH, 24, .1f);
    
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

