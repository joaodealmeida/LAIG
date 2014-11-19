#ifndef CIRCULARANIMATION_H
#define CIRCULARANIMATION_H

#define M_PI 3.14159265358979323846264338327950288

#include "Animation.h"

class CircularAnimation : public Animation
{
private:
	float center[3], radius, startang, rotang,distance,currentAngle,lastRotation,lastAnimation[3];
public:
	CircularAnimation(bool repeatable, std::string id, float span, float *center, float radius, float startang, float rotang) : Animation(repeatable, id, span){
		for(int i=0; i < 3; i++)
			this->center[i] = center[i];

		this->radius=radius;
		this->startang=startang;
		this->rotang=rotang;
	}

	void init(unsigned long t){
		startTime = t;
		reset = false;
		previousPoint = 0;
		this->distance = this->rotang - this->startang;
		currentAngle = 0;
		lastRotation=0;
		for(int i=0; i<3; i++)
			this->lastAnimation[i]=this->center[i];

	}
	void update(unsigned long t){
		if(this->reset){
			this->init(t);
			return;
		}
		unsigned long elapsedTime = t - this->startTime;
		this->startTime = t;
		this->currentAngle = distance * (elapsedTime / (span*1000)) + startang;
		if(currentAngle >= rotang){
			if (repeatable)
				this->reset = true;
			
			waiting=false;
			return;
		}

		lastRotation = currentAngle;
		float c1[3],c2[3],cf[3];
		c1[0]= cos(currentAngle * (M_PI/180));
		c1[1]=0;
		c1[2]=sin(currentAngle * (M_PI/180));
		for (int i = 0; i < 3; i++){
			c2[i]=c1[i]*this->radius;
			cf[i]=this->center[i]+c2[i];
			this->lastAnimation[i] = cf[i];
		}
		printf("LastAnimation %d, %d, %d \n", lastAnimation[0],lastAnimation[1],lastAnimation[2]);
	}
	void apply(){
		glTranslatef(this->lastAnimation[0],this->lastAnimation[1],this->lastAnimation[2]);
		glRotatef(currentAngle,0,1,0);
		printf("CurrentAngle: %d\n",currentAngle);
	}
	void setWaiting(bool opt){
		this->waiting = opt;
	}
	bool getWaiting(){
		return waiting;
	}

	~CircularAnimation(){}
};




#endif