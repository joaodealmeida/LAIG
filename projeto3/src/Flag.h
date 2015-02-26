#ifndef FLAG_H
#define FLAG_H


#include "Shader.h"
#include "Texture.h"
#include "Plane.h"

class Flag : public CGFobject, public Primitives
{
private:
	Shader *shader;
	Texture *text;
	Plane *plane;

	int wind;
	unsigned int tHold;

public:
	Flag(GLenum drawstyle, GLenum normal, Texture *text);
	~Flag(){}
	
	void draw();

	void setWind(int w);

	int getWind();
};
#endif