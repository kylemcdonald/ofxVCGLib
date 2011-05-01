#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	if(modelLoader.loadModel("duck_triangulate.dae", true)) {
		mesh = modelLoader.getMesh(0);
	} else {
		cout << "model failed to load" << endl;
	}

	glShadeModel(GL_SMOOTH);
	light.setup();
	ofEnableSeparateSpecularLight();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){	
	ofBackground(50, 50, 50, 0);
	ofSetColor(255);
	
	cam.begin();
	glEnable(GL_DEPTH_TEST);
	
	ofPushMatrix();
	mesh.drawFaces();
	
	/*
	if(hasJoined) {
		ofTranslate(200, 0, 0);
		joined->drawFaces();
	}
	*/
	
	ofPopMatrix();
	
	glDisable(GL_DEPTH_TEST);
	cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	//ofxVCG::smoothMesh(&mesh1, 3, 2);
	//joined = ofxVCG::joinMeshes(&mesh1, &mesh2);
	//hasJoined = true;
	
	//ofxVCG::cleanCloudPoints(&mesh.getVertices(), &out, 3.f);
}
