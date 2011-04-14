/*
 *  ofxVCGLib.h
 *
 *  Created by Makira on 11/03/03.
 *  Copyright 2011 yesMAYBEno. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "BunnyMesh.h"

#include "vcglib/vcg/simplex/vertex/base.h"
#include "vcglib/vcg/simplex/face/base.h"
#include "vcglib/vcg/simplex/face/topology.h"
#include "vcglib/vcg/complex/trimesh/base.h"
#include "vcglib/vcg/complex/trimesh/update/bounding.h"
#include "vcglib/vcg/complex/trimesh/update/topology.h"
#include "vcglib/vcg/complex/trimesh/update/normal.h"
#include "vcglib/vcg/complex/trimesh/update/flag.h"
#include "vcglib/vcg/complex/trimesh/create/ball_pivoting.h"
//#include "vcglib/vcg/space/box3.h"
#include "vcglib/vcg/space/normal_extrapolation.h"

#include "cmesh.h"
#include "ofxVCGPivot.h"

using namespace vcg;
using namespace tri;


class ofxVCGLib {

public:
	
	// for bunny mesh test :)
	void reconstructFaceBunny(float _radius = 0.22, 
							  float _clustering = 0.05,
							  float _angle = M_PI/2); 
	
	// if radius ==0 an autoguess for the ball pivoting radius is attempted 
	// otherwise the passed value (in absolute mesh units) is used.	
	void reconstructFacePointCloud(vector<float> point_cloud, 
								   float _radius = 0, 
								   float _clustering = 0.2,
								   float _angle = M_PI/2);
	bool addFace();

	float getRadius() { return radius; }
	float getClustering() { return clustering; }
	float getAngle() { return angle; }
	
	vector<float> getVertices();
	vector<int> getFaceIndices();
	int getFaceNum();
	
	CMesh m;	
	ofxVCGPivot<CMesh> *pivot;	
	BallPivoting<CMesh> *legacyPivot;
	
	float radius;
	float clustering;
	float angle;
	
};