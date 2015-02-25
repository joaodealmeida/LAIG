#ifndef VEHICLE_H
#define VEHICLE_H

#include <cmath>
#include "CGF\CGFobject.h"
#include "Primitives.h"
#include "Sphere.h"
#include "Patch.h"
#include "Torus.h"

class Vehicle : public CGFobject, public Primitives {
private:
	std::string style;
	Patch *patch;
	Sphere *sphere;
	Torus *torus;


public:
	Vehicle(GLenum drawstyle, GLenum normal) : Primitives(drawstyle, normal){
		sphere = new Sphere(drawstyle,normal, 2, 10, 10);
		torus = new Torus(drawstyle, normal, 0.5, 2, 12, 12);
		GLfloat *ctr = new GLfloat[9*3];
			ctr[0]=3;
			ctr[1]=0;
			ctr[2]=-3;
			ctr[3]=3;
			ctr[4]=-4;
			ctr[5]=0;
			ctr[6]=3;
			ctr[7]=0;
			ctr[8]=3;
			ctr[9]=0;
			ctr[10]=0;
			ctr[11]=-3;
			ctr[12]=0;
			ctr[13]=-4;
			ctr[14]=0;
			ctr[15]=0;
			ctr[16]=0;
			ctr[17]=3;
			ctr[18]=-3;
			ctr[19]=0;
			ctr[20]=-3;
			ctr[21]=-3;
			ctr[22]=-4;
			ctr[23]=0;
			ctr[24]=-3;
			ctr[25]=0;
			ctr[26]=3;
			patch = new Patch(drawstyle, normal, 2, 100, 100, "line", ctr);
	}
	~Vehicle(){}
	void draw(){

			glPushMatrix();
				glScalef(1,1,1);
				patch->draw();
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,1);
				glRotatef(180,1,0,0);
				patch->draw();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-3,0,0);
				sphere->draw();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(3,0,0);
				sphere->draw();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,2,0);
			glPopMatrix();
	}

};

#endif