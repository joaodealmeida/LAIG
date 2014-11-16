#pragma once

#include <cmath>
class Primitives
{
public:
	Primitives(GLenum drawstyle, GLenum normal) {
		quad = gluNewQuadric();
		gluQuadricDrawStyle(quad,drawstyle);
		gluQuadricNormals(quad,normal);
		gluQuadricOrientation(quad,GLU_OUTSIDE);
		gluQuadricTexture(quad,GL_TRUE);
	}
	virtual ~Primitives(){
		gluDeleteQuadric(quad);
	}
	virtual void draw(){}
	
	virtual void setDrawStyle(GLenum newstyle){
		gluQuadricDrawStyle(quad,newstyle);
	}

protected:
	GLUquadric *quad;
};

