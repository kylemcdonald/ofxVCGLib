#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	if(modelLoader.loadModel("duck_triangulate.dae", true)) {
		mesh1 = modelLoader.getMesh(0);
		mesh2 = modelLoader.getMesh(0);
		
	} else {
		cout << " model can't load? " << endl;
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
    ofSetColor(255, 255, 255, 255);
	
	ofPushMatrix();
		ofTranslate(300, 400, 0);
		ofRotate(180, 1.f, 0, 0);
		mesh1.drawFaces();//mesh1.drawWireframe();
		ofTranslate(200, 0, 0);
		mesh2.drawFaces();//mesh2.drawWireframe();
	ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofxVCG::smoothMesh(&mesh1, 3, 2);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}