/*
 *  ofxMeshFace.cpp
 *  emptyExample
 *
 *  Created by base on 15/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "ofxMeshFace.h"

ofxMeshFace::ofxMeshFace(ofVec3f a, ofVec3f b, ofVec3f c)
{
	
	if(!va) {
		va = new ofxVCGVertex(a);
		_face.V0(0) = va;
	} else {
		va->update(a);
	}
	
	if(!vb) {
		vb = new ofxVCGVertex(b);
		_face.V0(1) = vb;
	} else {
		va->update(a);
	}
	
	if(!vc) {
		vc = new ofxVCGVertex(c);
		_face.V0(2) = vc;
	} else {
		va->update(a);
	}
	
}

ofxMeshFace::ofxMeshFace()
{

}

void ofxMeshFace::addVertex(ofVec3f vert)
{
	//vcg::vert::Normal3fOcc vvert(vert);
	//vertices.push_back(vvert);
}