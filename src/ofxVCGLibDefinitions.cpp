/*
 *  ofxVCGLibDefinitions.cpp
 *  emptyExample
 *
 *  Created by base on 21/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxVCGLibDefinitions.h"

innerMesh::innerMesh(ofMesh* mesh)
{	
	
	Allocator<innerMesh>::AddVertices(*this,mesh->getNumVertices());
	Allocator<innerMesh>::AddFaces(*this,mesh->getNumIndices()/3 + 1);
	
	vector<ofColor>::iterator c_it;
	bool hasColors = mesh->getNumColors() > 0;
	if(hasColors) {
		c_it = mesh->getColors().begin();
	}
	
	//// this needs some thought
	VertexIterator vi = vert.begin();
	vector<ofVec3f>::iterator inVit = mesh->getVertices().begin();
	while(inVit != mesh->getVertices().end()) {
		
		if(hasColors) {
			(*vi).C().SetRGB((*c_it).r, (*c_it).g, (*c_it).b);
			++c_it;
		}
		
		(*vi) = ofxVCGVertex(*inVit);
		++inVit;
		++vi;
	}
	
	//// get all the faces
	FaceIterator fi = face.begin();
	vector<ofIndexType>::iterator indPtr = mesh->getIndices().begin();
	while( indPtr != mesh->getIndices().end()) {

		(*fi).V(0) = &vert[(unsigned int) (*indPtr)];
		++indPtr;
		(*fi).V(1) = &vert[(unsigned int) (*indPtr)];
		++indPtr;
		(*fi).V(2) = &vert[(unsigned int) (*indPtr)];
		++fi;
		++indPtr;
	}
	
	int dup = tri::Clean<innerMesh>::RemoveDuplicateVertex(*this);
	int unref =  tri::Clean<innerMesh>::RemoveUnreferencedVertex(*this);
	
	cout << " removed " << dup << " dup vertices and " << unref << " unref'd ones " << endl;
	
	// now get VCG to make it's own normals
	UpdateTopology<innerMesh>::FaceFace(*this);
	UpdateFlags<innerMesh>::FaceBorderFromFF(*this);
	UpdateNormals<innerMesh>::PerVertexNormalized(*this);
	// get all the colors if they're there
	//UpdateColor<innerMesh>::PerVertex(*this);
	
	
}

