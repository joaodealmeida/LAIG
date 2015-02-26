#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "Primitives.h"




class Animation
{
protected:
	
	bool reset, repeatable,waiting;
	float xTrans, yTrans, zTrans, rotation, span;
	std::string id;

public:
	Animation(bool repeatable, std::string id, float span){
		rotation = 0;
		reset = true;
		this->repeatable = repeatable;
		this->id = id;
		this->span = span;
		reset = true;
	}
	~Animation(){}
	virtual void update(unsigned long t) = 0;
	virtual void apply() = 0;
	virtual void init(unsigned long t) = 0;

	std::string getID(){
		return id;
	}
	virtual void setWaiting(bool opt) = 0;
	virtual bool getWaiting() = 0;

	unsigned long startTime;
	unsigned int previousPoint;
};
#endif