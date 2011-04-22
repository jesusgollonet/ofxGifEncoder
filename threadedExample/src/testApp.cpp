#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    frameW = 320;
    frameH = 240;
	ofSetFrameRate(30);
    vid.initGrabber(frameW,frameH);
	ofBackground(50, 40, 50);
	
	ofAddListener(ofxGifEncoder::OFX_GIF_ENCODER_EVENT_START, this, &testApp::onStart);
	ofAddListener(ofxGifEncoder::OFX_GIF_ENCODER_EVENT_END, this, &testApp::onComplete);
	
	bRecording	= false;
	status = "waiting";
}

//--------------------------------------------------------------
void testApp::update() { 
    vid.update();
	if(bRecording && vid.isFrameNew()) {
		ofxGifEncoder::addRGBFrame( vid.getPixels(), frameW, frameH, 1.f/30.f );
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	ofSetHexColor(0xffffff);
	if(bRecording) ofSetColor(255, 0, 0);
    vid.draw(0, 0);
	
	ofSetHexColor(0xffffff);
	ofDrawBitmapString("KEYS\n----\nspacebar: capture frame\ns: save gif", frameW+10, 20);
	ofDrawBitmapString("Status: "+status, frameW+10, 80);
}

//--------------------------------------------------------------
void testApp::onStart(int& i) {
	cout << "testApp :: onStart " << endl;
	status = "saving";
}

//--------------------------------------------------------------
void testApp::onComplete(string& s) {
	cout << "testApp :: onComplete " << s << endl;
	status = "save complete";
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
        case ' ':
            bRecording	= !bRecording;
            break;
        case 's':
			bRecording = false;
            ofxGifEncoder::save("test.gif", 256);
            break;
		case OF_KEY_DEL:
			ofxGifEncoder::clear();
			break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::exit() {
	ofxGifEncoder::exit();
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

