#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	if(modelLoader.loadModel("duck_triangulate.dae", true)) {
		mesh = modelLoader.getMesh(0);
	} else {
		cout << "model failed to load" << endl;
	}

	//light.setup();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){	
	ofBackground(50);
	ofSetColor(255);
	
	cam.begin();
	glEnable(GL_DEPTH_TEST);
	
	ofTranslate(-100, 0);
	mesh.drawWireframe();
	
	ofTranslate(200, 0);
	cleanMesh.drawWireframe();
	
	glDisable(GL_DEPTH_TEST);
	cam.end();
	
	ofDrawBitmapString("Press a key from 1-9 to clean the mesh.", 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	int amount = key - '1';
	amount = ofClamp(key, 1, 9);
	ofxVCG::cleanCloudPoints(&mesh, &cleanMesh, amount);
}
