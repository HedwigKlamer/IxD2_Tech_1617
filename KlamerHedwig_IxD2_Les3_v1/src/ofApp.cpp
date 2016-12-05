#include "ofApp.h"

void ofApp::setup() {
	ofSetBackgroundColor(ofColor::black);
	ofSetCircleResolution(30);
	ball.reset();

	grabber.setDeviceID(1);
	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT, true);
	//grabber.listDevices();


	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}

void ofApp::update() {
	bool wasReset = ball.update(mouseY);
	if (wasReset) {
		missedCount++;
	}
	grabber.update();

	if (grabber.isFrameNew()) {
		rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();



		for (int i = 0; i < GRABBER_WIDTH * GRABBER_HEIGHT; i++)
		{
			if (ofInRange(hue.getPixels()[i], selectedHue - HUE_MARGINE, selectedHue + HUE_MARGINE)) {
				filtered.getPixels()[i] = 255;
			}
			else {
				filtered.getPixels()[i] = 0;
			}
		}

		filtered.flagImageChanged();

		contours.findContours(filtered, 50, GRABBER_WIDTH*GRABBER_HEIGHT / 2, 1, false);
	}
}

void ofApp::draw() {
	ball.draw();

	ofDrawRectangle(ofGetWidth() - PADDLE_WIDTH,
		MIN(MAX(mouseY - PADDLE_HEIGHT / 2, 0), ofGetHeight() - PADDLE_HEIGHT),
		PADDLE_WIDTH, PADDLE_HEIGHT);

	ofDrawBitmapString("Missed: " + ofToString(missedCount), 10, 10);
	
	ofSetColor(ofColor::white);
	if (showVideo) {
		rgbImage.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	if (showContours) {
		contours.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofSetColor(ofColor::blue, 100);
	ofFill();
	for (int i = 0; i < contours.nBlobs; i++) {
		ofDrawCircle(contours.blobs[i].centroid.x*ofGetWidth() / GRABBER_WIDTH,
			contours.blobs[i].centroid.y*ofGetHeight() / GRABBER_HEIGHT, 20);
	}
	ofSetColor(ofColor::white);

}

void ofApp::keyPressed(int key) {
	if (key == 'v') {
		showVideo = !showVideo;
	}
	else if (key == 'c') {
		showContours = !showContours;
	}
}

void ofApp::mousePressed(int x, int y, int button) {

	selectedHue = hue.getPixels()[y * GRABBER_WIDTH + x];
	cout << "Selected: " << selectedHue << endl;


}
