#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	bool bSetupArduino;	// flag variable for setting up arduino once
	void keyPressed(int key);
	void exit();

private:
	ofArduino arduino;
	void setupArduino(const int& version);
	void digitalPinChanged(const int& pinNum);
	void analogPinChanged(const int& pinNum);

	ofSoundPlayer resAudio;
	ofSoundPlayer killAudio;

	int infraVal;
	int count;
	bool bEL;
	int flick;
	int random;
};
