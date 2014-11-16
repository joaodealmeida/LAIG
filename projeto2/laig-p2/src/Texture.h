#ifndef TEXTURE_H
#define TEXTURE_H

#include "CGF\CGFtexture.h"
class Texture : public CGFtexture
{
public:
	Texture(string name, string id, int s, int t) : CGFtexture(){
		CGFtexture::loadTexture(name);
		this->id=id;
		this->s=s;
		this->t=t;
	}

	string getID(){
		return id;
	}

	int getS(){
		return s;
	}
	int getT(){
		return t;
	}
private:

	std::string id;
	int s;
	int t;


};
#endif

