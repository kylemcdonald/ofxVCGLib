/*
 *  ofxVCGLib.cpp
 *
 *  Created by Makira on 11/03/03.
 *  Copyright 2011 yesMAYBEno. All rights reserved.
 *
 */

#include "ofxVCGLib.h"

void ofxVCGLib::reconstructFaceBunny(float _radius, 
									 float _clustering,
									 float _angle) {
	
	radius = _radius;
	clustering = _clustering;
	angle = _angle;
	
	m.face.clear();
	m.fn = 0;	
	m.Clear();	
	
	for (int i = 0; i < BUNNY_NUM_VERTICES; i++) {
		float x = gVerticesBunny[i*3];
		float y = gVerticesBunny[i*3+1];
		float z = gVerticesBunny[i*3+2];
		CVertex mv;
		mv.P() = Point3f(x,y,z);
		m.vert.push_back(mv);
		m.vn++;
//		cout << ofToString(x)+" "+ofToString(y)+" "+ofToString(z) << endl;
	}
//	cout << "total vertices = " + ofToString(m.vn) << endl;
	
	vcg::tri::UpdateBounding<CMesh>::Box(m);
	vcg::tri::UpdateNormals<CMesh>::PerFace(m);	
	tri::BallPivoting<CMesh> pivot(m, _radius, _clustering, _angle); 	
	pivot.BuildMesh();

}

void ofxVCGLib::reconstructFacePointCloud(vector<float> point_cloud, 
										  float _radius, 
										  float _clustering,
										  float _angle) {
	radius = _radius;
	clustering = _clustering;
	angle = _angle;	
	
	m.face.clear();
	m.fn = 0;	
	m.Clear();
	
	for (int i = 0; i < point_cloud.size()/3; i++) {
		float x = point_cloud[i*3];
		float y = point_cloud[i*3+1];
		float z = point_cloud[i*3+2];
		CVertex mv;
		mv.P() = Point3f(x,y,z);
		m.vert.push_back(mv);
		m.vn++;
		cout << ofToString(x)+" "+ofToString(y)+" "+ofToString(z) << endl;
	}
	cout << "point cloud size = " + ofToString((int)point_cloud.size()) << endl;
	cout << "total vertices = " + ofToString(m.vn) << endl;
	
	vcg::tri::UpdateBounding<CMesh>::Box(m);
	vcg::tri::UpdateNormals<CMesh>::PerFace(m);	
	legacyPivot = NULL;
	if (legacyPivot) delete legacyPivot;
	legacyPivot = new tri::BallPivoting<CMesh>(m, _radius, _clustering, _angle); 	
	legacyPivot->BuildMesh();	
	//NormalExtrapolation<vector<CVertex> >::ExtrapolateNormals(m.vert.begin(), m.vert.end(), 2);	
	
	//pivot = new tri::ofxVCGPivot<CMesh>(m, _radius, _clustering, _angle);
	
	int test = 9;
}

bool ofxVCGLib::addFace() {


	for(int i =0; i < 100; i++) {
//		for (int j = 0; j < m.vert.size(); j++) {
//			m.vert[j].ClearFlags();
//		}		
		//if(!pivot->seed()) cout << "seed fail!" << endl;
		cout << "trying add face : " + ofToString(i) << endl;
        if(1 == pivot->addFace()) return false;
	}
	
//	legacyPivot->last_seed = -1;
//	for (int j = 0; j < m.vert.size(); j++) {
//		m.vert[j].ClearFlags();
//	}	
//	while(1) {
//		for(int i = 0; i < 512; i++) {
//			if(!legacyPivot->front.size() && !legacyPivot->SeedFace()) return false;
//			legacyPivot->AddFace();
//			cout << "add face manually!!!!!!!!" << endl;
//		}
//    }	
//	return true;
}

vector<float> ofxVCGLib::getVertices() {
	
	vector<float> verts;
	for (int i = 0; i < m.vert.size(); i++) {
		verts.push_back(m.vert[i].P()[0]);
		verts.push_back(m.vert[i].P()[1]);
		verts.push_back(m.vert[i].P()[2]);
	}
	return verts;
	
}

vector<int> ofxVCGLib::getFaceIndices() {
	
	vector<int> faceIndices;
	for (int i = 0; i < m.face.size(); i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < m.vert.size(); k++) {
				float xc = m.face[i].V(j)->P()[0];
				float yc = m.face[i].V(j)->P()[1];
				float zc = m.face[i].V(j)->P()[2];				
				ofxVec3f c(xc, yc, zc);
				float xt = m.vert[k].P()[0];
				float yt = m.vert[k].P()[1];
				float zt = m.vert[k].P()[2];
				ofxVec3f t(xt, yt, zt);
				if (c == t) {
					faceIndices.push_back(k);
					break;
				}
			}
		}
	}
	return faceIndices;
	
}

int ofxVCGLib::getFaceNum() {
	
	return m.face.size();
	
}