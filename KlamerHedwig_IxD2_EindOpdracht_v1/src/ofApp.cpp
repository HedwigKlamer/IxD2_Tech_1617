/*Hallo Edwin! Welkom bij mijn code. In de bin map van dit project staat een schema
hoe dde arduino is aangesloten voor dit project. De audio staat helaas niet op GitHub 
Omdat dit te grote bestanden waren om erop te zetten. 
Veel plezier met het lezen van mijn code. Groetjes Hedwig*/
#include "ofApp.h"

//defining the pin from the arduino
#define PIN_INFRA 1
#define PIN_RELAIS 9


void ofApp::setup() {
	//initializing the arduino and making it ready to use
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest(); \
	bSetupArduino = false;	// flag so we setup arduino when its ready

	//initializing the audio of the project and telling which sound should play from the start and how load it should be
	resAudio.load("resAudio.wav");
	killAudio.load("killAudio.mp3");
	ofSoundSetVolume(0.2);
	resAudio.play();

	//Lighting the EL-wire as soon as the program is starting
	arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
}

void ofApp::update() {
	arduino.update();
	/*I wanted to make the EL-wire flicker when someone was near the light.
	I made to random variables for this 'flick' to give a random variable
	to tell if the light should be on or of. BUT because the relais takes
	1/10 of second to switch from on to off this kind of flicker was to fast
	for the relais and didn't light it up at all anymore because it was to busy
	turning the relais on and off again. So I made a second random variable with
	a bigger range so there was a bigger chance of a longer time of switching the
	relais.
	It's not the best way to code it, but it works :P I know I could this better
	with millis but I don't understand how I should use that in openframeworks.*/
	flick = ofRandom(0, 1); 
	random = ofRandom(0, 900);
	
	//check if someone is close enough to start the second audio
	if (infraVal >= 220){	
		ofSoundSetVolume(0.6);
		killAudio.play();
		//using the random variables I talked about earlier.
		if (flick == 0 && random >= 200) { 
			arduino.sendDigital(PIN_RELAIS, ARD_LOW);
		}
		else {
			arduino.sendDigital(PIN_RELAIS, ARD_HIGH);
		}
		
		
	}
	
}

//A script so I could test if the EL-wire worked when the infrared laser code wasn't there or didn't work
void ofApp::keyPressed(int key) {
	if (key == '1') {
		arduino.sendDigital(PIN_RELAIS, ARD_HIGH);	
	}
	else if (key == '2') {
		arduino.sendDigital(PIN_RELAIS, ARD_LOW);
	}
}

void ofApp::setupArduino(const int& version) {
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	// it is now safe to send commands to the Arduino
	bSetupArduino = true;
	// say what kind of output/input each pin has
	arduino.sendDigitalPinMode(PIN_RELAIS, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(PIN_INFRA, ARD_ANALOG);
	
	/*putting in listeners so I can see if something goes 
	wrong which element of the code this maybe be. */
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
	//making sure the EL-wire stops glowing if the program closes of, but somehow this didn't work
	arduino.sendDigital(PIN_RELAIS, ARD_LOW);
}
