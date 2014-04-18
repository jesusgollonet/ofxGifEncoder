#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    nFrames = 0;
    frameW  = 320;
    frameH  = 240;
    
    vid.initGrabber(frameW,frameH);
    
    gifEncoder.setup(frameW, frameH, .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
    
    ofBackground(50, 40, 50);

}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < nFrames; i ++) {
        txs[i]->draw(i* (frameW/2 + 5), frameH, frameW/2, frameH/2);
    }
    vid.draw(0, 0);
    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW+10, 20);
}

void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
}

void ofApp::captureFrame() {
    gifEncoder.addFrame(
                        vid.getPixels(),
                        vid.getWidth(),
                        vid.getHeight(),
                        vid.getPixelsRef().getBitsPerPixel(),
                        .1f
                        );
    
    ofTexture * tx = new ofTexture();
    tx->allocate(frameW, frameH, GL_RGB);
    tx->loadData(vid.getPixels(), frameW, frameH, GL_RGB);
    txs.push_back(tx);
    
    nFrames++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit(){
    gifEncoder.exit();
}