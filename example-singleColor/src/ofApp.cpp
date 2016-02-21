#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Create an instance of the LightingController class
	mController = ofxColorKinetics::LightingController::getInstance();

	// Add a power supply via the Controller -- all you need to know is the IP Address!
	mController->addPowerSupply("192.168.10.12");
	mController->setKinetVersion(1);

	// Add enough fixtures to fill up all 512 DMX Channels in a KiNET Packet.
	// All you need to know for each light is (1) which power supply it's attached to, (2) what its first DMX Address is, and (3) how many addressable components it has (one R,G,B triplet = 1)
	for (int i = 0; i < 170; i++) {
		mController->addFixture("192.168.10.12", 3*i + 1, 1);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	//Every time you'd like to update the lights, get each light:
	for (auto fixture : mController->getAllFixtures()) {
		//set each light to a color
		fixture->setColor(0xFF, 0x00, 0xFF);
	}
	
	//And ask the controller to 'tick' -- which is send a message to every power supply with the updated DMX Universe
	mController->tick(0x00);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	std::string power_supplies = " Power Supplies \n ============== \n ";
	for (auto psu : mController->getAllPowerSupplies()) {
		power_supplies += psu->getIpAddress();
		power_supplies += " \n ";
	}
	ofDrawBitmapString(power_supplies, 50, 50);

	std::string fixtures = " Fixtures       \n ============== \n ";
	for (auto f : mController->getAllFixtures()) {
		fixtures += std::to_string(f->getStartingAddress());
		fixtures += " \n ";
	}
	ofDrawBitmapString(fixtures, 250, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
