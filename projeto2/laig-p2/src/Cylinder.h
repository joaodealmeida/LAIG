#ifndef CYLINDER_H
#define CYLINDER_H

#include "CGF\CGFobject.h"
#include "Primitives.h"

class Cylinder : public CGFobject, public Primitives
{
public:
	Cylinder(GLenum drawstyle, GLenum normal, float base, float top,float height, int slices, int stacks) : Primitives(drawstyle, normal){
		this->base=base;
		this->top=top;
		this->height=height;
		this->slices=slices;
		this->stacks=stacks;
	}

	void draw(){
		glPushMatrix();
			gluCylinder(quad,base,top,height,slices,stacks);

			glPushMatrix();
				//glRotatef(180, 1,0,0);
				glTranslatef(0,0,height);
				gluDisk(quad, 0.0f, top, slices, 1);
			glPopMatrix();

			glPushMatrix();
				glRotatef(180,0,1,0);
				gluDisk(quad, 0.0f, base, slices, 1);
			glPopMatrix();

		glPopMatrix();

	}

private:
	float base, top, height;
	int slices,stacks;

};


#endif