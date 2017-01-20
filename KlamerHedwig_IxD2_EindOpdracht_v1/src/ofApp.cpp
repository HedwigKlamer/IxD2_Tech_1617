#include "ofApp.h"

#define PIN_INFRA 1
#define PIN_RELAIS 9


void ofApp::setup() {
	//initializing the arduino and making it ready to use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest(); \
	bSetupArduino = false;	// flag so we setup arduino when its ready

	resAudio.load("resAudio.wav");
	killAudio.load("killAudio.mp3");
	ofSoundSetVolume(0.2);
	resAudio.play();

	arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
}

void ofApp::update() {
	arduino.update();
	flick = ofRandom(0, 1);
	random = ofRandom(0, 900);
	arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
	

	if (infraVal >= 220){
		ofSoundSetVolume(0.6);
		killAudio.play();
		if (flick == 0 && random >= 200) {
			arduino.sendDigital(PIN_RELAIS, ARD_LOW);
		}
		else {
			arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
		}
		
		
	}
	
}

void ofApp::draw(){

}

void ofApp::keyPressed(int key) {
	if (key == '1') {
		arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
		bEL = true;
	}
	else if (key == '2') {
		arduino.sendDigital(PIN_RELAIS, ARD_LOW);
		bEL = false;
	}
}

void ofApp::setupArduino(const int& version) {
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// it is now safe to send commands to the Arduino
	bSetupArduino = true;
	// say what kind of output/input each pin has
	arduino.sendDigitalPinMode(PIN_RELAIS, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(PIN_INFRA, ARD_ANALOG);
	
	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
	ofLogNotice() << "Start "  << endl;
}

void ofApp::digitalPinChanged(const int& pinNum) {
	ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;
}

void ofApp::analogPinChanged(const int& pinNum) {
	ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
	infraVal = arduino.getAnalog(pinNum);
}

void ofApp::exit() {
	if (bEL == true) {
		arduino.sendDigital(PIN_RELAIS, ARD_LOW);
	}
}
