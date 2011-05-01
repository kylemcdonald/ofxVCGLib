#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	if(modelLoader.loadModel("duck_triangulate.dae", true)) {
		mesh = modelLoader.getMesh(0);
	} else {
		cout << "model failed to load" << endl;
	}
	
	useShading = false;
	
	light.setup();
}

//--------------------------------------------------------------
void testApp::update(){
	if(useShading) {
		ofEnableLighting();
	} else {
		ofDisableLighting();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(50);
	ofSetColor(255);
	
	cam.begin();
	glEnable(GL_DEPTH_TEST);
	
	ofTranslate(-100, 0);
	if(useShading) {
		mesh.drawFaces();
	} else {
		mesh.drawWireframe();
	}
	
	ofTranslate(200, 0);
	if(useShading) {
		cleanMesh.drawFaces();
	} else {
		cleanMesh.drawWireframe();
	}
	
	glDisable(GL_DEPTH_TEST);
	cam.end();
	
	ofDrawBitmapString("Press a key from 1-9 to clean the mesh.", 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 's') {
		useShading = !useShading;
	} else {
		int amount = key - '1';
		amount = ofClamp(amount, 1, 9) * 3;
		ofxVCG::cleanCloudPoints(&mesh, &cleanMesh, amount);
	}
}
