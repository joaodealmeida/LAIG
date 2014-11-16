#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <CGF\CGFobject.h>
#include "Primitives.h"

class Patch : public CGFobject, public Primitives {
public:
	Patch(GLenum drawstyle, GLenum normal, int order, int partsU, int partsV, std::string compute, GLfloat *controlPoints);
	~Patch();
	void draw();


private:
	int order, partsU, partsV;
	std::string compute;

	void calcTextPoints(int order);

	GLfloat *controlPoints;
	static const GLfloat normalComponent[4][3];
	GLfloat *texturePoints;
	//static const GLfloat colorPoints[4][4];
	
	
};

#endif