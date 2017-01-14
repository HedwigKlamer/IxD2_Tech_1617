#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp {
	
public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	ofVideoGrabber grabber;
	ofxCvHaarFinder haarFinder;
	
	bool drawBox = true;
	bool drawImage = false;

	ofImage image;
	

	

private:
	
};
