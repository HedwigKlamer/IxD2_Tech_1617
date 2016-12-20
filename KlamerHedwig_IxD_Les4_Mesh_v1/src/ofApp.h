#pragma once

#include "ofMain.h"

#define MESH_WIDTH 50
#define MESH_HEIGHT 50
#define MESH_SIZE 10

#define IMAGE_WIDTH 259
#define IMAGE_HEIGHT 194
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofMesh mesh;
		ofImage image;
		ofEasyCam cam;

		ofPlanePrimitive plane;
		
		
};
