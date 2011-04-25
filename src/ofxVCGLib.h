/*
 *  ofxVCGLib.h
 *
 *  Created by Makira on 11/03/03.
 *  Copyright 2011 yesMAYBEno. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#include <math.h>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component_ocf.h>
#include <vcg/simplex/face/topology.h>
#include <vcg/space/normal_extrapolation.h>

#include<vcg/simplex/face/component_ocf.h>

#include <vcg/complex/trimesh/base.h>

#include <vcg/complex/trimesh/update/bounding.h>
#include <vcg/complex/trimesh/update/topology.h>
#include <vcg/complex/trimesh/update/normal.h>
#include <vcg/complex/trimesh/update/flag.h>
#include <vcg/complex/trimesh/create/ball_pivoting.h>

#include <vcg/complex/trimesh/base.h>

#include <vcg/complex/intersection.h>

//#include <vcg/complex/trimesh/refine.h>
//#include <vcg/complex/trimesh/refine_loop.h>

#include <vcg/complex/trimesh/bitquad_creation.h>

// to clean up a mesh
#include <vcg/complex/trimesh/append.h>
#include <vcg/complex/trimesh/clean.h>
#include<vcg/complex/trimesh/smooth.h>
#include <vcg/complex/trimesh/clip.h>

#include "ofxVCGLibDefinitions.h"
#include "ofxMeshFace.h"
#include "vcgRayMeshIntersection.h"

using namespace vcg;
using namespace tri;

enum meshConstructionAlgo { BALL_PIVOT_CONSTRUCTION, MARCHING_CUBES_CONSTRUCTION };


namespace ofxVCG {
	
	void refineMesh(ofMesh* mesh, int steps, int type);
	void smoothMesh(ofMesh* mesh, int steps, int smoothingAmount);
	
	void simplifyNode(ofNode* mesh, int degree);

	ofMesh* intersectMeshes(vector<ofMesh> meshes);
	ofMesh* differenceMeshes(vector<ofMesh> meshes);

	ofMesh* joinMeshes(ofMesh* toBeParent, ofMesh* toBeChild);
	ofMesh* joinMeshes(ofMesh* toBeParent, vector<ofMesh*> toBeJoined);

	ofNode* intersectNodes(vector<ofNode> nodes);
	ofNode* differenceNodes(vector<ofNode> nodes);
	ofNode* joinNodes(vector<ofNode> nodes);

	bool meshIntersection(ofMesh* aMesh, ofMesh* bMesh);
	bool nodeIntersection(ofNode* aNode, ofNode* bNode);

	// smart pointers would be freaking sweet here
	ofMesh* createMeshFromPoints(vector<ofVec3f> points, int degreeOfFidelity, meshConstructionAlgo useMeshConstructionAlgo);
	ofMesh* createMeshFromPoints(vector<float> points, int degreeOfFidelity, meshConstructionAlgo useMeshConstructionAlgo);

	void pointsToPlane(vector<ofVec2f> points);
	void cleanMesh(ofMesh* mesh);

	// don't really like the c-style-ness of this
	void getNeighboringFaces(ofxMeshFace* face, ofMesh* mesh);
	void getFacesFromMesh(vector<ofxMeshFace>* faces, ofMesh* mesh);
	void constructMeshFromFaces(ofMesh* mesh, vector<ofxMeshFace>* faces);
	vcgRayMeshIntersection getFacesForRay(ofxVCGRay ray, ofMesh* mesh);
	
	// aka the kyle mcdonald functions
	void vcgMeshToOf(innerMesh* inner, ofMesh* mesh);
	void vcgVec3ToOf(innerMesh* inner, ofMesh* mesh);
	
};