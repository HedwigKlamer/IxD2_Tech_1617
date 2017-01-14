#pragma once

#include "ofMain.h"
#include "Ball.h"
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

	static const int PADDLE_WIDTH = 20;
	static const int PADDLE_HEIGHT = 500;

	
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
	int centerContour;
	
	bool showHSVComponents = true;
	bool showContours = true;
	bool showFilter = true;
	bool showVideo = true;

private:
	Ball ball;
	int missedCount;
};
