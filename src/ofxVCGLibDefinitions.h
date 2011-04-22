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
#include<vcg/complex/trimesh/allocate.h>
//#include<vcg/complex/trimesh/refine.h>
#include<vcg/complex/trimesh/update/flag.h>


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
	public Vertex<ofxVCGTypes, vertex::Coord3f, vertex::BitFlags,vertex::Normal3f, vertex::Color4b>  
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
	
	ofVec3f& toOf()
	{
		ofVec.x = P().X();
		ofVec.y = P().Y();
		ofVec.z = P().Z();
		return ofVec;
	}
	
private:
	
	ofVec3f ofVec;
	
};

// used to store face info
// only used in vcg->ofxMeshFace conversion
class innerMeshFace:public Face<ofxVCGTypes, face::FFAdj, face::VertexRef, face::BitFlags, face::Normal3f> {
	
};

// used to store edge info
class innerEdge:public Edge<ofxVCGTypes>{
	
};

class innerMesh:public vcg::tri::TriMesh<vector<ofxVCGVertex>, vector<innerMeshFace> > {
	
	public:
	
	vector<int> mesh_indices;
	
	innerMesh() {}
	
	innerMesh(ofMesh* mesh);
	
	vector<float> getVertices() {
		
		vector<float> verts;
		for (int i = 0; i < vert.size(); i++) {
			verts.push_back(vert[i].P()[0]);
			verts.push_back(vert[i].P()[1]);
			verts.push_back(vert[i].P()[2]);
		}
		return verts;
		
	}
	
	// this is hellishly slow :(
	// 
	vector<int> getFaceIndices() 
	{	
		vector<int> faceIndices;
		for (int i = 0; i < face.size(); i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				for (int k = 0; k < vert.size(); k++) 
				{
					if(face[i].V(j))
					{
						float xc = face[i].V(j)->P()[0];
						float yc = face[i].V(j)->P()[1];
						float zc = face[i].V(j)->P()[2];				
						ofVec3f c(xc, yc, zc);
						float xt = vert[k].P()[0];
						float yt = vert[k].P()[1];
						float zt = vert[k].P()[2];
						ofVec3f t(xt, yt, zt);
						if (c == t) 
						{
							faceIndices.push_back(k);
							break;
						}
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

