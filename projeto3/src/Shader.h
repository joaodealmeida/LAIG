#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include "CGF\CGFapplication.h"
#include "CGF\CGFShader.h"



class Shader : public CGFshader
{
private:
	GLint imgLoc;
	GLint windLoc;
	GLint tLoc;
	float elapsedTime;

	CGFtexture *text;


public:
	Shader(CGFtexture *text, std::string vertexSPath, std::string fragmentSPath);
	~Shader();
	
	void bind(float d, float w);





};

#endif