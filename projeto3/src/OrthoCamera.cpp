#include "OrthoCamera.h"
#include "CGF\CGFapplication.h"

OrthoCamera::OrthoCamera(std::string id, bool enabled){
	this->id=id;
	this->enabled=enabled;
}

OrthoCamera::~OrthoCamera(){
}

void OrthoCamera::setEnabled(bool opt){
        enabled=opt;
}

bool OrthoCamera::getEnabled(){
	return enabled;
}

/*string OrthoCamera::getID(){
	return id;
}*/

void OrthoCamera::applyView(){
	if(direction.compare("x") == 0)
		glRotatef(-90.f,0,1,0);
	else if(direction.compare("y") == 0)
		glRotatef(90.f,1,0,0);
}

void OrthoCamera::updateProjectionMatrix(int width, int height){
	float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left*aspect,right*aspect,bottom,top,near,far);
}


void OrthoCamera::setNear(float v){
	near=v;
}
void OrthoCamera::setFar(float v){
	far=v;
}

void OrthoCamera::setDirection(std::string dir){
	direction=dir;
}
void OrthoCamera::setLeft(float v){
	left=v;
}

void OrthoCamera::setRight(float v){
	right=v;
}

void OrthoCamera::setTop(float v){
	top=v;
}

void OrthoCamera::setBottom(float v){
	bottom=v;
}

std::string OrthoCamera::getDirection(){
	return direction;
}

float OrthoCamera::getNear(){
	return near;
}
float OrthoCamera::getFar(){
	return far;
}
float OrthoCamera::getLeft(){
	return left;
}

float OrthoCamera::getRight(){
	return right;
}

float OrthoCamera::getTop(){
	return top;
}
float OrthoCamera::getBottom(){
	return bottom;
}