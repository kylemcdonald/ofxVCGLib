/*
 *  ofxMeshFace.h
 *  emptyExample
 *
 */

#pragma once 

#include "ofMain.h"
#include "ofxVCGLibDefinitions.h"

//#include <vcg/simplex/vertex/component_occ.h>
//#include <vcg/simplex/face/component_occ.h>
//#include <vcg/container/vector_occ.h>

//using namespace vcg;

class ofxMeshFace
{

public:
	
	ofxMeshFace(ofVec3f a, ofVec3f b, ofVec3f c);
	ofxMeshFace();
	
	//const ofxMeshFace();
	//const ofxMeshFace(ofVec3f a, ofVec3f b, ofVec3f c);
	
	void addVertex(ofVec3f vert);
	
private:
	
	innerMeshFace _face;
	
	ofxVCGVertex *va;
	ofxVCGVertex *vb;
	ofxVCGVertex *vc;

};

