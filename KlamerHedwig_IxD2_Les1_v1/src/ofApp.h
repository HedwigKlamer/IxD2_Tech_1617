#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define HUE_MARGINE 5

class ofApp : public ofBaseApp {

	static const int GRABBER_WIDTH = 320;
	static const int GRABBER_HEIGHT = 240;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	
	ofVideoGrabber grabber;

	ofxCvColorImage rgbImage;
	ofxCvColorImage hsvImage;

	ofxCvGrayscaleImage hue;
	ofxCvGrayscaleImage saturation;
	ofxCvGrayscaleImage brightness;

	ofxCvGrayscaleImage filtered;
	ofxCvContourFinder finder;

	ofxCvContourFinder contours;

	int selectedHue;

	bool showHSVComponents = true;
	bool showFilter = true;
	bool showContours = true;
	bool showVideo = true;
};
