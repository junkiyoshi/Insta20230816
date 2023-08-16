#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum());

	int span = 20;
	int size = span * 0.75;

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

	for (int x = span * -24; x <= span * 24; x += span) {

		for (int y = span * -24; y <= span * 24; y += span) {

			auto len = glm::length(glm::vec2(x, y));
			if (len > 200 && len < 400) {

				auto height = ofMap(ofNoise(x * 0.005, y * 0.005, len * 0.005 + ofGetFrameNum() * 0.03), 0, 1, -300, 300);
				auto power = ofMap(abs(300 - len), 0, 100, 1, 0);
				height *= power;

				ofFill();
				ofSetColor(ofColor(0));
				ofDrawBox(glm::vec3(x, y, height * 0.5), size, size, height);

				ofNoFill();
				ofSetColor(ofColor(255));
				ofDrawBox(glm::vec3(x, y, height * 0.5), size, size, height);
			}

			ofSetColor(128);
			ofDrawRectangle(x, y, size, size);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}