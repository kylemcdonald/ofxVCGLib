/*
 *  rayMeshIntersectionData.h
 *  ofxVCGEx
 *
 *  Created by base on 25/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxMeshFace.h"

class vcgRayMeshIntersection {
	
	// return references with these	
public:
	
	
	ofxMeshFace intersectedFace;
	ofVec3f baricentricCenter;
	ofVec3f hitPoint;
	
	vcgRayMeshIntersection() {}
	
	// so you can copy these into a vector or other container
	vcgRayMeshIntersection(const vcgRayMeshIntersection& copy) {
		intersectedFace = copy.intersectedFace;
		baricentricCenter = copy.baricentricCenter;
		hitPoint = copy.hitPoint;
	}
	
	vcgRayMeshIntersection& operator =(const vcgRayMeshIntersection& rhs) {
		
		if(this == &rhs)
			return *this;
		
		intersectedFace = rhs.intersectedFace;
		baricentricCenter = rhs.baricentricCenter;
		hitPoint = rhs.hitPoint;
		
		return *this;
	}
	
};