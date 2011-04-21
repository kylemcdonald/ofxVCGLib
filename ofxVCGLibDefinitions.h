/*
 *  ofxVCGLibDefinitions.h
 *  emptyExample
 *
 */


#pragma once


#include "ofMain.h"
#include <vcg/space/point3.h> 
#include <vcg/container/vector_occ.h> 
#include <vcg/simplex/vertex/base.h> 
#include <vcg/simplex/vertex/component_ocf.h>
#include <vcg/simplex/face/component_ocf.h>

#include<vcg/simplex/vertex/base.h>
#include<vcg/simplex/face/base.h>
#include<vcg/simplex/face/topology.h>

// basics
#include<vcg/complex/trimesh/base.h>
#include <vcg/complex/trimesh/update/topology.h>
#include <vcg/complex/trimesh/update/normal.h>

// to clean up a mesh
#include<vcg/complex/trimesh/clean.h>
#include<vcg/complex/trimesh/smooth.h>

#include "ofxVCGCloud.h"
#include "ofxVCGVoxel.h"

#define __FLT_EVAL_METHOD__ 0

using namespace vcg;


// base types
class ofxVCGVertex;

class innerMeshFace; // composition -> ofxMeshFace
class innerMesh; // converted to ofMesh
class innerEdge;

struct ofxVCGTypes:public UsedTypes<Use<ofxVCGVertex>::AsVertexType, Use<innerEdge>::AsEdgeType, Use<innerMeshFace>::AsFaceType>{};

class ofxVCGVertex: 
	public Vertex<ofxVCGTypes, vertex::Coord3f, vertex::Normal3f, vertex::BitFlags, vertex::Mark, vertex::VFAdj, vertex::Qualityf>  
{

public:
	
	ofxVCGVertex() {}
	
	ofxVCGVertex(ofVec3f sourceVec3f)
	{
		P().X() = sourceVec3f.x;
		P().Y() = sourceVec3f.y;
		P().Z() = sourceVec3f.z;
	}
	
	void update(ofVec3f sourceVec3f)
	{
		P().X() = sourceVec3f.x;
		P().Y() = sourceVec3f.y;
		P().Z() = sourceVec3f.z;
	}
	
};

// used to store face info
// only used in vcg->ofxMeshFace conversion
class innerMeshFace:public Face<ofxVCGTypes, face::InfoOcf, face::FFAdjOcf,  face::VertexRef, face::BitFlags > {
	
};

// used to store edge info
class innerEdge:public Edge<ofxVCGTypes>{
	
};

class innerMesh:public vcg::tri::TriMesh<vector<ofxVCGVertex>,vector<innerMeshFace> > {
public:
	
	innerMesh() {}
	
	innerMesh(ofMesh* mesh) {
		int i;
		
		/// whoa, this needs some thought
		vector<ofVec3f>::iterator v_it = mesh->getVertices().begin();
		while(v_it != mesh->getVertices().end()) {
			ofxVCGVertex v(*v_it);
			vert.push_back(v);
			++v_it;
		}
		
		// need these or let them get calc'd in vcg?
		/*vector<ofVec3f>::iterator n_it = mesh->getNormals().begin();
		while(n_it != mesh->getNormals().end()) {
			ofxVCGVertex n(*n_it);
			face.normals.push_back(n);
			++n_it;
		}*/
	}
	
	vector<float> getVertices() {
		
		vector<float> verts;
		for (int i = 0; i < vert.size(); i++) {
			verts.push_back(vert[i].P()[0]);
			verts.push_back(vert[i].P()[1]);
			verts.push_back(vert[i].P()[2]);
		}
		return verts;
		
	}
	
	vector<int> getFaceIndices() {
		
		vector<int> faceIndices;
		for (int i = 0; i < face.size(); i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < vert.size(); k++) {
					float xc = face[i].V(j)->P()[0];
					float yc = face[i].V(j)->P()[1];
					float zc = face[i].V(j)->P()[2];				
					ofVec3f c(xc, yc, zc);
					float xt = vert[k].P()[0];
					float yt = vert[k].P()[1];
					float zt = vert[k].P()[2];
					ofVec3f t(xt, yt, zt);
					if (c == t) {
						faceIndices.push_back(k);
						break;
					}
				}
			}
		}
		return faceIndices;
		
	}
	

};

class ofxVCGRay {
	
public:
	ofVec3f begin, direction;
	
};

// other typedefs

typedef SimpleVolume<SimpleVoxel> ofxVCGVolume;
typedef vcg::GridStaticPtr<innerMesh::FaceType, innerMesh::ScalarType> innerMeshGrid;

