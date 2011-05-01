/*
 *  ofxVCGLibDefinitions.cpp
 *  ofxVCGEx
 *
 *  Created by base on 21/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxVCGLibDefinitions.h"

// todo - this really needs to get all the indices from 
// the ofMesh so it can get them back when turning this
// back into an ofMesh
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
		if(indPtr != mesh->getIndices().end())
		{
			++indPtr;
		}
		if(indPtr != mesh->getIndices().end())
		{
			(*fi).V(1) = &vert[(unsigned int) (*indPtr)];
			++indPtr;
		}
		if(indPtr != mesh->getIndices().end())
		{
			(*fi).V(2) = &vert[(unsigned int) (*indPtr)];
			++indPtr;
		}
		++fi;
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


// this is hellishly slow :(
// 
vector<int> innerMesh::getFaceIndices() 
{	
	vector<int> faceIndices;
	/*for (int i = 0; i < face.size(); i++) 
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
	 }*/


	FaceIterator fi;
	for(fi = face.begin(); fi != face.end(); ++fi)
	{
		
		int v0 = (unsigned int)( (*fi).V(0) - &(*this->vert.begin() ));
		int v1 = (unsigned int)( (*fi).V(1) - &(*this->vert.begin() ));
		int v2 = (unsigned int)( (*fi).V(2) - &(*this->vert.begin() ));
																					  
		cout << v0 <<  " " << v1 << " " << v2 << endl;
		
		if(v0 < vert.size() && v0 > -1) faceIndices.push_back(v0);
		if(v1 < vert.size() && v1 > -1) faceIndices.push_back(v1);
		if(v2 < vert.size() && v2 > -1) faceIndices.push_back(v2);
	}
	
	return faceIndices;
	
}

