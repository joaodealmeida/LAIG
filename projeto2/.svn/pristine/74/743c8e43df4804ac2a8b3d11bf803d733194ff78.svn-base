#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "CGF\CGFcamera.h"

#include <string>

class PerspectiveCamera : public CGFcamera

{
private:
	bool enabled;
	std::string id;
	float near,far,angle;
	bool defaultCamera;


public:

	PerspectiveCamera(std::string id, bool enabled);
	~PerspectiveCamera(void);

	virtual void applyView();
	virtual void updateProjectionMatrix(int width, int height);

	void setEnabled(bool opt);


	void setNear(float v);
	float getNear();

	std::string getID();

	void setFar(float v);
	float getFar();

	void setAngle(float v);
	float getAngle();

	bool getEnabled();
	float getAspect();

	void setTarget(float * targetArray);
	void setPosition(float * positionArray);
	float * getPosition();
	float * getTarget();


};
#endif