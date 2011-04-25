/*
 *  ofxMeshFace.cpp
 *  emptyExample
 *
 *
 */


#include "ofxMeshFace.h"

ofxMeshFace::ofxMeshFace(ofVec3f a, ofVec3f b, ofVec3f c)
{
	
	vv0.update(a);
	vv1.update(a);
	vv2.update(a);
	
	ofv0 = a;
	ofv1 = a;
	ofv2 = a;
	
}

ofxMeshFace::ofxMeshFace(ofxVCGVertex a, ofxVCGVertex b, ofxVCGVertex c)
{
	
	// not sure about copying these this way...
	vv0.P() = a.P();
	vv0.N() = a.N();
	vv0.Flags() = a.Flags();
	vv0.C() = a.C();
	
	// not sure about copying these this way...
	vv2.P() = b.P();
	vv2.N() = b.N();
	vv2.Flags() = b.Flags();
	vv2.C() = b.C();
	
	// not sure about copying these this way...
	vv1.P() = c.P();
	vv1.N() = c.N();
	vv1.Flags() = c.Flags();
	vv1.C() = c.C();
	
	ofv0 = vv0.toOf();
	ofv1 = vv1.toOf();
	ofv2 = vv2.toOf();
	
	ofn0 = vv0.normalToOf();
	ofn1 = vv1.normalToOf();
	ofn2 = vv2.normalToOf();	
}

ofxMeshFace::ofxMeshFace(innerMesh::FacePointer fp)
{
	// not sure about copying these this way...
	vv0.P() = fp->V(0)->P();
	vv0.N() = fp->V(0)->N();
	vv0.Flags() = fp->V(0)->Flags();
	vv0.C() = fp->V(0)->C();
	
	// not sure about copying these this way...
	vv2.P() = fp->V(2)->P();
	vv2.N() = fp->V(2)->N();
	vv2.Flags() = fp->V(2)->Flags();
	vv2.C() = fp->V(2)->C();
	
	// not sure about copying these this way...
	vv1.P() = fp->V(1)->P();
	vv1.N() = fp->V(1)->N();
	vv1.Flags() = fp->V(1)->Flags();
	vv1.C() = fp->V(1)->C();
	
	ofv0 = vv0.toOf();
	ofv1 = vv1.toOf();
	ofv2 = vv2.toOf();

	ofn0 = vv0.normalToOf();
	ofn1 = vv1.normalToOf();
	ofn2 = vv2.normalToOf();
}

ofxMeshFace::ofxMeshFace()
{
}

ofxMeshFace::ofxMeshFace(const ofxMeshFace& copy) 
{
	vv0 = copy.vv0;
	vv1 = copy.vv1;
	vv2 = copy.vv2;

	ofv0 = copy.ofv0;
	ofv1 = copy.ofv1;
	ofv2 = copy.ofv2;
	
	ofn0 = copy.ofn0;
	ofn1 = copy.ofn1;
	ofn2 = copy.ofn2;
	
}

ofxMeshFace& ofxMeshFace::operator=(const ofxMeshFace& rhs)
{
	
	if (this == &rhs)      // Same object?
		return *this;
	
	vv0 = rhs.vv0;
	vv1 = rhs.vv1;
	vv2 = rhs.vv2;
	
	ofv0 = rhs.ofv0;
	ofv1 = rhs.ofv1;
	ofv2 = rhs.ofv2;
	
	ofn0 = rhs.ofn0;
	ofn1 = rhs.ofn1;
	ofn2 = rhs.ofn2;
	
	return *this;
}

void ofxMeshFace::addThisToMesh(innerMesh* m)
{
	Allocator<innerMesh>::AddVertices(*m,3);
	Allocator<innerMesh>::AddFaces(*m,1);
	
	innerMesh::VertexPointer ivp[3];
	innerMesh::VertexIterator vi = m->vert.begin();
	ivp[0]=&*vi;
	(*vi).P() = Point3f( 1.0, 1.0, 1.0);
	++vi;
	ivp[1]=&*vi;
	(*vi).P() = Point3f (-1.0, 1.0,-1.0);
	++vi;
	ivp[2]=&*vi;
	(*vi).P() = Point3f (-1.0,-1.0, 1.0);
	++vi;
	
	innerMesh::FaceIterator fi = m->face.begin();
	(*fi).V(0)=ivp[0];
	(*fi).V(1)=ivp[1];
	(*fi).V(2)=ivp[2]; 

}
