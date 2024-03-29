#include "PerspectiveCamera.h"
#include "CGF\CGFapplication.h"

PerspectiveCamera::PerspectiveCamera(std::string id, bool enabled){
	this->id=id;
	this->enabled=enabled;
}

PerspectiveCamera::~PerspectiveCamera(){
}

void PerspectiveCamera::setEnabled(bool opt){
        enabled=opt;
}

string PerspectiveCamera::getID(){
	return id;
}


void PerspectiveCamera::applyView(){
	if (mode==EXAMINE_MODE)
	{
		gluLookAt(
			position[0],position[1],position[2],
			target[0],target[1],target[2],
			0,1,0);

		glRotatef(rotation[0], 1.f, 0.f, 0.f);
		glRotatef(rotation[1], 0.f, 1.f, 0.f);
		glRotatef(rotation[2], 0.f, 0.f, 1.f);

	}
	else
	{
		glRotatef(rotation[0], 1.f, 0.f, 0.f);
		glRotatef(rotation[1], 0.f, 1.f, 0.f);
		glRotatef(rotation[2], 0.f, 0.f, 1.f);

		glTranslatef(position[0], position[1], position[2]);
	}
}

void PerspectiveCamera::updateProjectionMatrix(int width, int height){
		float aspect= (float)width / (float)height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle,aspect,near,far);
}


void PerspectiveCamera::setNear(float v){
	near=v;
}
void PerspectiveCamera::setFar(float v){
	far=v;
}

void PerspectiveCamera::setAngle(float v){
	angle=v;
}
bool PerspectiveCamera::getEnabled(){
	return enabled;
}



float PerspectiveCamera::getNear(){
	return near;
}
float PerspectiveCamera::getFar(){
	return far;
}
float PerspectiveCamera::getAngle(){
	return angle;
}

void PerspectiveCamera::setTarget(float * targetArray){
	this->target[0]=targetArray[0];
	this->target[1]=targetArray[1];
	this->target[2]=targetArray[2];
}
void PerspectiveCamera::setPosition(float * positionArray){
	this->position[0]=positionArray[0];
	this->position[1]=positionArray[1];
	this->position[2]=positionArray[2];
}
float * PerspectiveCamera::getPosition(){
	return position;
}
float * PerspectiveCamera::getTarget(){
	return target;
}