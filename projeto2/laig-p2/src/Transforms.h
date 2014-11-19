#ifndef Transforms_H
#define Transforms_H

#include "GL\gl.h"
#include <string>

class Transforms
{
public:
	Transforms(){}
	~Transforms(){}
	virtual void apply(){}

	virtual float *getTransformMatrix(){
		return &(transformMatrix[0][0]);
	}

protected:
	float destination[3];
	float transformMatrix[4][4];

};

class Translate : public Transforms
{
public:
	Translate(float *destination){
		this->destination[0]=destination[0];
		this->destination[1]=destination[1];
		this->destination[2]=destination[2];

		glLoadIdentity();
		glTranslatef(destination[0],destination[1],destination[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,&transformMatrix[0][0]);
	}
	~Translate(){}
	
	void apply(){
		glTranslatef(destination[0],destination[1],destination[2]);
	}

private:

};

class Rotate : public Transforms
{
public:
	Rotate(std::string axis, float angle){
		this->axis=axis;
		this->angle=angle;

		glLoadIdentity();
		if(axis == "x") glRotatef(angle,1,0,0);
		if(axis == "y") glRotatef(angle,0,1,0);
		if(axis == "z") glRotatef(angle,0,0,1);
		glGetFloatv(GL_MODELVIEW_MATRIX,&transformMatrix[0][0]);
	}

	~Rotate(){
	}

	void apply(){
		if(axis == "x") glRotatef(angle,1,0,0);
		if(axis == "y") glRotatef(angle,0,1,0);
		if(axis == "z") glRotatef(angle,0,0,1);
	}

private:
	std::string axis;
	float angle;
};

class Scale : public Transforms
{
public:
	Scale(float *factor){
		this->destination[0]=factor[0];
		this->destination[1]=factor[1];
		this->destination[2]=factor[2];

		glLoadIdentity();
		glScalef(destination[0],destination[1],destination[2]);
		glGetFloatv(GL_MODELVIEW_MATRIX,&transformMatrix[0][0]);
	}
	void apply(){
		glScalef(destination[0],destination[1],destination[2]);
	}

	~Scale();

private:

};

#endif

