/*
 *  ofxMeshFace.h
 *  ofxVCGEx
 *
 */

#pragma once 

#include "ofMain.h"
#include "ofxVCGLibDefinitions.h"

class ofxMeshFace
{

public:
	
	ofxMeshFace(ofVec3f a, ofVec3f b, ofVec3f c);
	ofxMeshFace(ofxVCGVertex a, ofxVCGVertex b, ofxVCGVertex c);
	ofxMeshFace(innerMesh::FacePointer fp);
	ofxMeshFace();
	
	ofxMeshFace(const ofxMeshFace& copy);
	ofxMeshFace& operator =(const ofxMeshFace& rhs);
	
	
	
	ofVec3f& toOfV0() { return ofv0; }
	ofVec3f& toOfV1() { return ofv1; }
	ofVec3f& toOfV2() { return ofv2; }
	
	ofVec3f& toOfN0() { return ofn0; }
	ofVec3f& toOfN1() { return ofn1; }
	ofVec3f& toOfN2() { return ofn2; }
	
	ofxVCGVertex& toVcgV0() { return vv0; }
	ofxVCGVertex& toVcgV1() { return vv1; }
	ofxVCGVertex& toVcgV2() { return vv2; }
	
	Point3f toVcgN0() { return vv0.N(); }
	Point3f toVcgN1() { return vv1.N(); }
	Point3f toVcgN2() { return vv2.N(); }
	
	Point3f toVcgP0() { return vv0.P(); }
	Point3f toVcgP1() { return vv1.P(); }
	Point3f toVcgP2() { return vv2.P(); }

	void addThisToMesh(innerMesh* m);
	
protected:
	
	// there's no innerMeshFace b/c those are created using the 
	// addThisToMesh method
	
	// normals are contained in the ofxVCGVertex
	ofxVCGVertex vv0;
	ofxVCGVertex vv1;
	ofxVCGVertex vv2;
	
	// normals aren't contained in the ofVec3, so they're separate here
	ofVec3f ofv0;
	ofVec3f ofv1;
	ofVec3f ofv2;
	
	ofVec3f ofn0;
	ofVec3f ofn1;
	ofVec3f ofn2;

};

