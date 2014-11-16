#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "CGF\CGFobject.h"
#include "Primitives.h"

class Triangle : public CGFobject, public Primitives
{
public:
	Triangle(GLenum drawstyle, GLenum normal, float x1, float y1, float z1 , float x2 , float y2, float z2, float x3, float y3, float z3) : Primitives(drawstyle,normal){
		this->x1=x1;this->y1=y1;this->z1=z1;
		this->x2=x2;this->y2=y2;this->z2=z2;
		this->x3=x3;this->y3=y3;this->z3=z3;

		float base1 = sqrtf(pow(this->x2 - this->x1, 2) + pow(this->y2 - this->y1, 2) + pow(this->z2 - z1, 2));
		float hipotenusa = sqrtf(pow(this->x3 - this->x1, 2) + pow(this->y3 - this->y1, 2) + pow(this->z3 - this->z1, 2));
		float teta = acos((this->x1 * this->x2 + this->y1 * this->y2 + this->z1 * this->z2) / (base1 * hipotenusa));
		float base2 = hipotenusa * cos(teta);

		float height = sqrt(pow(hipotenusa, 2) - pow(base2, 2));

		delta_s1=base1;delta_s2=base2;delta_t= height;

		calcNormal();
	}

	void setDrawStyle(GLenum newstyle){
			style=newstyle;
	}

	void draw(){

		if(style == GLU_LINE) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		if(style == GLU_FILL) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		if(style == GLU_POINT) glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		glPushMatrix();
		glBegin(GL_TRIANGLES);
        
        {
			glNormal3f(normal[0],normal[1],normal[2]);
			glTexCoord2f(0, 0);
			glVertex3f(x1, y1, z1);
			glTexCoord2f(delta_s1, 0);
			glVertex3f(x2, y2, z2);
			glTexCoord2d(delta_s2, delta_t);
			glVertex3f(x3, y3, z3);
        }
		glEnd();
		glPopMatrix();
	}

	void calcNormal(){
		float v[3];
		float u[3];

		v[0] = x2 - x1;
		v[1] = y2 - y1;
		v[2] = z2 - z1;

		u[0] = x3 - x1;
		u[1] = y3 - y1;
		u[2] = z3 - z1;

		normal[0] = (u[1] * v[2]) - (u[2] * v[1]);
		normal[1] = (u[2] * v[0]) - (u[0] * v[2]);
		normal[2] = (u[0] * v[1]) - (u[1] * v[0]);
}


private:
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	float delta_s1,delta_s2,delta_t,normal[3];
	GLenum style;
};

#endif