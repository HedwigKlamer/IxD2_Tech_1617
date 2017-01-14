#include "ofApp.h"

#define GRABBER_WIDTH 640 
#define GRABBER_HEIGHT 480

void ofApp::setup() {
	ofSetBackgroundColor(ofColor::black);
	grabber.setDeviceID(1);
	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT);

	haarFinder.setup("haarcascade_eyes.xml");
	image.load("eyes.png");
}

void ofApp::update() {
	grabber.update();
	if (grabber.isFrameNew()) {
		haarFinder.findHaarObjects(grabber.getPixels(), 80, 80);
	}
	
}

void ofApp::draw() {
	grabber.draw(0, 0);
	//ofNoFill();
	//ofSetColor(ofColor::black);
	for (int i = 0; i < haarFinder.blobs.size(); i++) {
		ofRectangle blobBoundingRectangle = haarFinder.blobs[i].boundingRect;
		
		if (drawBox) {
			ofDrawRectangle(blobBoundingRectangle);
		}
		if (drawImage) {
			image.draw(blobBoundingRectangle);
		}
	}
	
}

void ofApp::keyPressed(int key) {
	if (key == 'b') {
		drawBox = !drawBox;
	}
	else if (key == 'i')
		drawImage = !drawImage;
}


