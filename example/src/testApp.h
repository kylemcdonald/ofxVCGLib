#pragma once

#include "ofMain.h"

#include "ofxVCGLib.h"
#include "ofxAssimpModelLoader.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	ofMesh mesh, cleanMesh;
	ofxAssimpModelLoader modelLoader;
	
	ofLight	light;
	
	bool useShading;
	
	ofEasyCam cam;
};
