#ifndef SPHERE_H
#define SPHERE_H

#include "CGF\CGFobject.h"
#include "Primitives.h"

class Sphere : public CGFobject, public Primitives
{
public:
	Sphere(GLenum drawstyle, GLenum normal, float radius, int slices, int stacks) :  Primitives(drawstyle, normal){

		this->radius=radius;
		this->slices=slices;
		this->stacks=stacks;
	}
	
	void draw(){
		glPushMatrix();
		gluSphere(quad,radius,slices,stacks);
		glPopMatrix();
	}

private:
	float radius;
	int slices, stacks;
};
#endif