
/*All functions are explainen at the ofApp.cpp :)*/
#pragma once
#include "ofMain.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	
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
	int flick;
	int random;
};
