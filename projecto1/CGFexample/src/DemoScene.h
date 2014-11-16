#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "XMLScene.h"


class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void applyGlobals();
	void applyCameras();
	void applyLights();
	void applyGraph();
	void drawScene(Node* n);
	void update(unsigned long t);
	XMLScene * getParserResults();

	//Interface
	int drawstyle;
	vector<CGFlight *> sceneLights;
	vector<CGFcamera *> sceneCameras;
	DemoScene(string name){
		this->name=name;
	}
	~DemoScene();
private:
	string name;
	XMLScene *x1;
	//Control variables
	bool globalsApplyDone;



	//Graph
	Graph* sceneGraph;

	PerspectiveCamera *p1;
	OrthoCamera *o1;
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
};

#endif