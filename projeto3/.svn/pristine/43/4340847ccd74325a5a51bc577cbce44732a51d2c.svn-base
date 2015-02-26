#pragma once

#include <string>
#include <vector>
#include "Appearance.h"
#include "Transforms.h"
#include "Animation.h"

class Node
{
public:
	Node(string id){
		this->id=id;
		inherited_app=false;
		parent=nullptr;
		hasDisplayList=false;
		idDisplayList=-1;
		calculated = false;
	}

	~Node(void){}

	void setAppearanceRef(std::string app_ref){
		this->appearance_ref=app_ref;
	}

	std::string getAppearanceRef(){
		return appearance_ref;
	}

	std::string getNodeId(){
		return id;
	}

	void setAppearance(Appearance *app){
		this->appearance=app;
	}

	void setInheritedApp(){
		inherited_app=true;
	}

	Appearance * getAppearance(){
		if(inherited_app)
			return (this->parent->getAppearance());

		return appearance;
		
	}

	void addDescendantsRef(std::string desc_ref){
		this->descendants_ref.push_back(desc_ref);
	}

	std::vector<std::string> getDescendantsRef(){
		return descendants_ref;
	}

	void addDescendants(Node *n){
		descendants.push_back(n);
	}

	std::vector<Node *> getDescendants(){
		return descendants;
	}

	void addTransform(Transforms *t){
		transforms.push_back(t);
	}

	std::vector<Transforms *> getTransforms(){
		return transforms;
	}

	void addPrimitive(Primitives *p1){
		primitives.push_back(p1);
	}

	vector<Primitives *> getPrimitives(){
		return primitives;
	}
		
	void setParent(Node* n){
		this->parent=n;
	}

	Node * getParent(){
		return parent;
	}
	void draw(){

		if(hasDisplayList && idDisplayList != 1 )
			glCallList(idDisplayList);

		else{
			if(hasDisplayList && idDisplayList == -1){
				idDisplayList = glGenLists(1);
				glNewList(idDisplayList,GL_COMPILE);

			}

			applyTransformation();

			for(int i=0; i< primitives.size(); i++)
				primitives[i]->draw();
		}

		if(hasDisplayList && idDisplayList == -1)
			glEndList();

		if(hasDisplayList)
			glCallList(idDisplayList);




	}

	void applyTransformation(){
		if(parent == nullptr){
			for(int i=0; i< transforms.size(); i++)
				transforms[i]->apply();
			return;
		}

		for(int i=0; i< parent->getTransforms().size(); i++)
			parent->getTransforms()[i]->apply();

		for(int i=0; i< transforms.size(); i++)
			transforms[i]->apply();

	}

	float * getTransformationMatrix(){
		return &transformMatrix[0][0];
	}
	void setTransformationMatrix( float matrix[4][4]){
		for(int i=0; i<4; i++){
			for( int j=0; j<4; j++)
				transformMatrix[i][j]=matrix[i][j];
		}
	}

	void setDisplayList(bool opt){
			hasDisplayList=opt;
			idDisplayList = -1;
			calculated = false;
	}

	bool getHasDisplayList(){
		return hasDisplayList;
	}

	int getIDDisplayList(){
		return idDisplayList;
	}

	void setIDDisplayList(int index){
		idDisplayList = index;
	}

	bool isCalculated(){
		return this->calculated;
	}

	void setCalculated(bool calculated) {
		this->calculated = calculated;
	}

	void addAnimation(Animation *a1){
		this->animations.push_back(a1);
	}

	void addAnimationRef(std::string a1){
		this->animations_ref.push_back(a1);
	}

	std::vector<std::string> getAnimationsRef(){
		return animations_ref;
	}
	std::vector<Animation *> getAnimations(){
		return this->animations;
	}

	void startAnimation(unsigned long t){
		Animation *a=nullptr;
		if(animations.empty()) return;

		for(int i=0; i < animations.size(); i++){
			a=animations[i];
			if(a->getWaiting()){
				a->update(t);
				break;
			}
		}
	}

private:
	std::string id;
	std::vector<Node* > descendants;
	std::vector<std::string> descendants_ref;
	std::vector<Transforms *> transforms;
	std::vector<Primitives *> primitives;
	Node *parent;
	Appearance *appearance;
	std::vector<Animation*> animations;
	std::vector<string> animations_ref;
	std::string appearance_ref;
	float transformMatrix[4][4];
	bool inherited_app;
	bool hasDisplayList;
	int idDisplayList;
	bool calculated;

};

