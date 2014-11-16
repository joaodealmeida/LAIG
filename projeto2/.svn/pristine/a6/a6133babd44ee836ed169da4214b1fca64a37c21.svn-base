#ifndef TORUS_H
#define TORUS_H

#include "CGF\CGFobject.h"
#include "Primitives.h"
#define M_PI 3.14159265358979323846264338327950288

class Torus : public CGFobject, public Primitives
{
public:
	Torus(GLenum drawstyle, GLenum normal, float inner, float outer, float slices, float loops) : Primitives(drawstyle, normal){
		this->inner = outer;
        this->outer = inner;
        this->slices = slices;
        this->loops = loops;

	}
	
void setDrawStyle(GLenum newstyle){
			style=newstyle;
}

void draw(){
	GLfloat vNormal[3];   
	double majorStep = 2.0f*3.14 / slices;   
	double minorStep = 2.0f*3.14 / loops;   
	int i, j;   

	if(style == GLU_LINE) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	if(style == GLU_FILL) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	if(style == GLU_POINT) glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

	for (i=0; i<slices; ++i)    
	{   
		double a0 = i * majorStep;   
		double a1 = a0 + majorStep;   
		GLfloat x0 = (GLfloat) cos(a0);   
		GLfloat y0 = (GLfloat) sin(a0);   
		GLfloat x1 = (GLfloat) cos(a1);   
		GLfloat y1 = (GLfloat) sin(a1);

		glBegin(GL_TRIANGLE_STRIP);   
		for (j=0; j<=loops; ++j)    
		{   
			double b = j * minorStep;   
			GLfloat c = (GLfloat) cos(b);   
			GLfloat r = outer * c + inner;   
			GLfloat z = outer * (GLfloat) sin(b);   

			// First point   
			glTexCoord2f((float)(i)/(float)(slices), (float)(j)/(float)(loops));   
			vNormal[0] = x0*c;
			vNormal[1] = y0*c;
			vNormal[2] = z/inner;
			///normalizar
			double magnitude2=sqrt(vNormal[0]*vNormal[0]+vNormal[1]*vNormal[1]+vNormal[2]*vNormal[2]);
			vNormal[0] /=magnitude2;
			vNormal[1] /=magnitude2;
			vNormal[2] /= magnitude2;

			glNormal3fv(vNormal);   
			glVertex3f(x0*r, y0*r, z);   

			glTexCoord2f((float)(i+1)/(float)(slices), (float)(j)/(float)(loops));   
			vNormal[0] = x1*c;   
			vNormal[1] = y1*c;   
			vNormal[2] = z/inner;   
			glNormal3fv(vNormal);   
			glVertex3f(x1*r, y1*r, z);   
		}   
		glEnd();   
	}
}
private:
	float inner, outer;
	int slices, loops;
	double *vertex, *_normal;
	GLenum style;
};



#endif