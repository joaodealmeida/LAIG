#ifndef COMPONENTS_H
#define COMPONENTS_H

class Components
{
public:
	Components(float *ambient, float *diffuse , float *s){
	this->ambient[0]=ambient[0];
	this->ambient[1]=ambient[1];
	this->ambient[2]=ambient[2];
	this->ambient[3]=ambient[3];

	this->diffuse[0]=diffuse[0];
	this->diffuse[1]=diffuse[1];
	this->diffuse[2]=diffuse[2];
	this->diffuse[3]=diffuse[3];

	this->specular[0]=s[0];
	this->specular[1]=s[1];
	this->specular[2]=s[2];
	this->specular[3]=s[3];
}
	~Components();

	float * getAmbient(){
		return ambient;
	}
	float * getDiffuse(){
		return diffuse;
	}
	float * getSpecular(){
		return specular;
	}

private:
	float ambient[4],diffuse[4],specular[4];

};
#endif

