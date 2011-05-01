#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	hasJoined = false;
	
	if(modelLoader1.loadModel("duck_triangulate.dae", true)) {
		mesh1 = modelLoader1.getMesh(0);
		
	} else {
		cout << " model 1 can't load? " << endl;
	}
	
	if(modelLoader2.loadModel("soccer.DAE", true)) {
		mesh2 = modelLoader2.getMesh(0);
	} else {
		cout << " model 2 can't load? " << endl;
	}
	
	glShadeModel(GL_SMOOTH);
	light.setup();
	ofEnableSeparateSpecularLight();
	
	int i = 0;
	while( i < 1000 )
	{
		in.push_back(ofVec3f(ofRandom(100), ofRandom(100), ofRandom(100)));
		i++;
	}
	
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
	ofRotate(180, -1.f, 0, 0);
	ofTranslate(200, 0, 0);
	mesh2.drawFaces();
	
	if(hasJoined)
	{
		ofTranslate(200, 0, 0);
		joined->drawFaces();
	}
	
	ofPopMatrix();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	//ofxVCG::smoothMesh(&mesh1, 3, 2);
	//joined = ofxVCG::joinMeshes(&mesh1, &mesh2);
	//hasJoined = true;
	
	ofxVCG::cleanCloudPoints(&in, &out, 3.f);
	
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