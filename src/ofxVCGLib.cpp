/*
 *  ofxVCGLib.cpp
 *
 *  Created by Makira on 11/03/03.
 *  Copyright 2011 yesMAYBEno. All rights reserved.
 *
 */

#include "ofxVCGLib.h"

ofMesh* ofxVCG::intersectMeshes(vector<ofMesh> meshes)
{
	
	//tri::Append<MyMesh,MyMesh>::Mesh(ml,mr);
}

ofMesh* ofxVCG::createMeshFromCloud(ofxVCGCloud* cloud)
{

	// up to you to manage this one, but this really should be a smart ptr
	ofMesh* mesh = new ofMesh();
	return mesh;
	
}

void ofxVCG::cleanMesh(ofMesh* mesh)
{
	
	innerMesh m(mesh);
	
	int dup = tri::Clean<innerMesh>::RemoveDuplicateVertex(m);
	int unref =  tri::Clean<innerMesh>::RemoveUnreferencedVertex(m);

	// updating
	UpdateBounding<innerMesh>::Box(m);
	UpdateNormals<innerMesh>::PerFaceNormalized(m);
	UpdateNormals<innerMesh>::PerVertexAngleWeighted(m);
	UpdateNormals<innerMesh>::NormalizeVertex(m);
	UpdateFlags<innerMesh>::FaceProjection(m);
	
	// copy back
	vcgMeshToOf(&m, mesh);
}

// make this read in files too
void ofxVCG::smoothMesh(ofMesh* mesh, int steps, int smoothingAmount)
{
	innerMesh m(mesh);
	
	// probably want different meshes for each method
	// but the laplacian is one of the simpler
	tri::Smooth<innerMesh>::VertexCoordLaplacian(m, steps); 
	
	vcgMeshToOf(&m, mesh);
	
}

void ofxVCG::vcgMeshToOf(innerMesh* inner, ofMesh* mesh)
{
	// this desperately needs to be smarter, big meshes are going to
	// be bears to deal with.
	mesh->clear();
	
	innerMesh::VertexIterator vi = inner->vert.begin();
	while(vi != inner->vert.end())
	{
		mesh->addVertex(vi->toOf());
		ofVec3f vec(vi->N().X(), vi->N().Y(), vi->N().Z());
		mesh->addNormal(vec);
		++vi;
	}
	
	vector<int> faceIndices = inner->getFaceIndices();
	vector<int>::iterator fi = faceIndices.begin();
	while(fi != faceIndices.end())
	{
		mesh->addIndex(*fi);
		++fi;
	}
}
							

void ofxVCG::refineMesh(ofMesh* mesh, int steps, int type=0)
{
	
	float length = 0;
	innerMesh m(mesh);
	int i;
	for(i=0;i < steps;++i)			
	{
		switch(type)
		{
				// some weird template madness, this doesn't compile :|
/*			case 0:
				vcg::Refine<innerMesh, MidPoint<innerMesh> >(m,MidPoint<innerMesh>(&m),length);
				break;
			case 1:
				tri::RefineOddEven<innerMesh, tri::OddPointLoop<innerMesh>, tri::EvenPointLoop<innerMesh> >(m, tri::OddPointLoop<innerMesh>(), tri::EvenPointLoop<innerMesh>(), length);
				break;
			case 2:
				tri::BitQuadCreation<innerMesh>::MakePureByCatmullClark(m);
				tri::UpdateNormals<innerMesh>::PerBitQuadFaceNormalized(m);
				break;      
			case 3:
				tri::BitQuadCreation<innerMesh>::MakePureByRefine(m);
				tri::UpdateNormals<innerMesh>::PerBitQuadFaceNormalized(m);
				break;
			case 4:
				Refine<innerMesh, MidPointButterfly<innerMesh> >(m,MidPointButterfly<innerMesh>(),length);
				break; */
		}		
	}
	
}

// hmm
void ofxVCG::simplifyNode(ofNode* node, int degree)
{
}


ofMesh* ofxVCG::differenceMeshes(vector<ofMesh> meshes)
{
}

ofMesh* ofxVCG::joinMeshes( ofMesh* toBeParent, vector<ofMesh*> toBeJoined )
{
	innerMesh mP(toBeParent);
	
	vector<ofMesh*>::iterator meshIt = toBeJoined.begin();
	while(meshIt != toBeJoined.end()) {
		innerMesh mC( *meshIt ); // messy
		tri::Append<innerMesh,innerMesh>::Mesh(mP,mC); // join them
		++meshIt;
	}
	
	tri::Clean<innerMesh>::RemoveDuplicateVertex(mP); // now clean it up 
	
}

ofMesh* ofxVCG::joinMeshes( ofMesh* toBeParent, ofMesh* toBeChild )
{
	innerMesh mP(toBeParent);
	innerMesh mC(toBeChild);
	
	tri::Append<innerMesh,innerMesh>::Mesh(mP,mC); // join them
	tri::Clean<innerMesh>::RemoveDuplicateVertex(mP); // now clean it up 
	
	ofMesh* mesh = new ofMesh();
	
	vcgMeshToOf(&mP, mesh);
	
	return mesh;
	
}



ofNode* ofxVCG::intersectNodes(vector<ofNode> nodes)
{
}


ofNode* ofxVCG::differenceNodes(vector<ofNode> nodes)
{
}


ofNode* ofxVCG::joinNodes(vector<ofNode> nodes)
{
}



bool ofxVCG::meshIntersection(ofMesh* aNode, ofMesh* bNode)
{
}


bool ofxVCG::nodeIntersection(ofNode* aNode, ofNode* bNode)
{
}



// smart pointers would be freaking sweet here
ofxVCGCloud* ofxVCG::createCloudFromMesh(ofMesh* mesh)
{
}


ofMesh* ofxVCG::createMeshFromPoints(vector<ofVec3f> points, int degreeOfFidelity)
{
}


ofMesh* ofxVCG::createMeshFromPoints(vector<ofVec2f> points, int degreeOfFidelity)
{
}



ofxVCGCloud* ofxVCG::createCloudFromPoints(vector<ofVec2f> points)
{
}



ofxVCGCloud* ofxVCG::createCloudFromPoints(vector<ofVec3f> points)
{
	
	innerMesh m;
	
	m.face.clear();
	m.fn = 0;	
	m.Clear();
	
	vector<ofVec3f>::iterator pIt = points.begin();
	while (pIt != points.end()) {
		ofxVCGVertex mv;
		mv.P() = Point3f(pIt->x,pIt->y,pIt->z);
		m.vert.push_back(mv);
		m.vn++;
		
		++pIt;
	}
	
	vcg::tri::UpdateBounding<innerMesh>::Box(m);
	vcg::tri::UpdateNormals<innerMesh>::PerFace(m);	
	
	/*
	legacyPivot = NULL;
	if (legacyPivot) delete legacyPivot;
	legacyPivot = new tri::BallPivoting<innerMesh>(m, _radius, _clustering, _angle); 	
	legacyPivot->BuildMesh();
	
	NormalExtrapolation<vector<CVertex> >::ExtrapolateNormals(m.vert.begin(), m.vert.end(), 2);	
	
	pivot = new tri::ofxVCGPivot<CMesh>(m, _radius, _clustering, _angle);
	*/
	
}

void ofxVCG::getFacesForRay(ofxVCGRay ray, ofMesh* mesh)
{
	innerMesh m(mesh);
	float t;
	float maxDist = 1000;
	
	// Create a static grid (for fast indexing) and fill it
	innerMeshGrid grid;
	grid.Set(m.face.begin(), m.face.end());
	
	// convert the ray
	vcg::Ray3f vcg_ray;
	vcg::Point3f beg(ray.begin.x, ray.begin.y, ray.begin.z);
	vcg::Point3f dir(ray.direction.x, ray.direction.y, ray.direction.z);
	vcg_ray.SetOrigin(beg);
	vcg_ray.SetDirection(dir);
	
	// now actually find the face
	innerMeshFace *rf = tri::DoRay<innerMesh,innerMeshGrid>(m, grid, vcg_ray, maxDist, t);
	
}

void ofxVCG::pointsToPlane(vector<ofVec2f> points)
{
}


// don't really like the c-style-ness of this
void ofxVCG::getNeighboringFaces(ofxMeshFace* face, ofMesh* mesh)
{
}

void ofxVCG::getFacesFromMesh(vector<ofxMeshFace>* faces, ofMesh* mesh){
}

void ofxVCG::constructMeshFromFaces(ofMesh* mesh, vector<ofxMeshFace>* faces){
}


/*
void reconstructFaceBunny(float _radius, 
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

void reconstructFacePointCloud(vector<float> point_cloud, 
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

bool addFace() {


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

vector<float> getVertices() {
	
	vector<float> verts;
	for (int i = 0; i < m.vert.size(); i++) {
		verts.push_back(m.vert[i].P()[0]);
		verts.push_back(m.vert[i].P()[1]);
		verts.push_back(m.vert[i].P()[2]);
	}
	return verts;
	
}

vector<int> getFaceIndices() {
	
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

int getFaceNum() {
	
	return m.face.size();
	
}
*/