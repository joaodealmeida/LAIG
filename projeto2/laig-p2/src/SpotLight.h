#include "CGF\CGFlight.h"
#include "Components.h"

class SpotLight : public CGFlight
{
public:
	SpotLight(unsigned int lightid, float* pos, float *dir, std::string id, bool marker, float* target, float angle,float exponent) : CGFlight(lightid, pos, dir){
		this->sid=id;
		this->marker=marker;
		this->target[0]=target[0];
		this->target[1]=target[1];
		this->target[2]=target[2];
		this->position[0]=pos[0];
		this->position[1]=pos[1];
		this->position[2]=pos[2];
		CGFlight::setAngle(angle);
		this->exponent=exponent;
		glLightf(lightid, GL_SPOT_EXPONENT, exponent);
		lightComponent = nullptr;

		for(int i=0; i<3; i++){
			direction[i]=target[i]-position[i];
		}

	}
	
	void setComponent (Components *c1){
		lightComponent=c1;
		setAmbient(c1->getAmbient());
		setDiffuse(c1->getDiffuse());
		setSpecular(c1->getSpecular());
	}
	
	bool getMarker(){
		return marker;
	}

	bool getEnabled(){
		return enabled;
	}

	string getID(){
		return sid;
	}

private:
	std::string sid;
	bool marker;
	float target[4],angle,exponent;
	Components *lightComponent;
};





