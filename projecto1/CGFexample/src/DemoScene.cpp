#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "Rectangle.h"
#include "Cylinder.h"
#include "Torus.h"

#include <math.h>

#include "CGFappearance.h"

void DemoScene::init() 
{
	x1 = new XMLScene(const_cast<char *>(name.c_str()));


	for(OmniLight *o1 : x1->omniLightVec)
		sceneLights.push_back(o1);
	for(SpotLight *s1 : x1->spotLightVec)
		sceneLights.push_back(s1);

	for(OrthoCamera *o1 : x1->OrthocamVec)
		sceneCameras.push_back(o1);
	for(PerspectiveCamera *p1 : x1->PerscamVec)
		sceneCameras.push_back(p1);
	
	applyLights();
	applyGlobals();

	obj = new Torus(GL_FILL,GL_SMOOTH,4,3,10,12);





	//Enables lighting computations
	//glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	//glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light
	//float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	//light0 = new CGFlight(GL_LIGHT0, light0_pos);
	//light0->enable();*/
	//applyGlobals();
	//applyLights();
	// Defines a default normal
	//glNormal3f(0,0,1);
	/*for(PerspectiveCamera *p1 : x1->PerscamVec)
		if(p1->getEnabled()){
			CGFscene::activeCamera = p1;
			CGFapplication::activeApp->forceRefresh();

		}


	for(OrthoCamera *o1 : x1->OrthocamVec)
		if(o1->getEnabled()){
			CGFscene::activeCamera = o1;
			CGFapplication::activeApp->forceRefresh();

		}*/

	/*
	p1 = new PerspectiveCamera("1",true);
	p1->setAngle(45);
	p1->setNear(0.1);
	p1->setFar(50);
	float pos[3] = {10.5 , 8.0, 12.0};
	p1->setPosition(pos);
	float tar[3] = {8.5 , 4.0, 8.5};
	p1->setTarget(tar);*/

	/*o1 = new OrthoCamera("2",true);
	o1->setDirection("y");
	o1->setBottom(-10);
	o1->setTop(10);
	o1->setLeft(-10);
	o1->setRight(10);
	o1->setNear(-10);
	o1->setFar(10);
	

	


	

	CGFscene::activeCamera = o1;
	CGFapplication::activeApp->forceRefresh()`*/

	//obj=new Cylinder(GL_FILL,GL_FLAT,1,1,5,10,10);
	//obj2=new Torus(GL_FILL, GL_FLAT,10,3,10,10);
	//obj3=new Triangle(GL_FILL,GL_FLAT,-1,1,1,1,1,1,0,2.5,0);
	//obj4=new Rectangle(GL_FILL,GL_FLAT,0,0,20,20);
	materialAppearance=new CGFappearance();
	//textureAppearance=new CGFappearance("../data/pyramid.jpg",GL_REPEAT, GL_REPEAT);
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

	setUpdatePeriod(30);
}

XMLScene* DemoScene::getParserResults(){
	return x1;
}

void DemoScene::applyGlobals(){
	//Drawing
	if (x1->drawMode.compare("fill") == 0) {
		glPolygonMode(GL_FRONT_AND_BACK,GLU_FILL);
	}else if(x1->drawMode.compare("line") == 0){
		glPolygonMode(GL_FRONT_AND_BACK,GLU_LINE);
	}else
		glPolygonMode(GL_FRONT_AND_BACK,GLU_POINT);



	if (x1->shading.compare("flat") == 0) {
		glShadeModel(GL_FLAT);
	}else
		glShadeModel(GL_SMOOTH);


	glClearColor(x1->drawBackground[0],x1->drawBackground[1],x1->drawBackground[2],x1->drawBackground[3]);


	//Culling

	if (x1->cullFace.compare("none") == 0) {
		glCullFace(GL_NONE);
	}else if(x1->cullFace.compare("back") == 0){
		glCullFace(GL_BACK);
	}else if (x1->cullFace.compare("front") == 0){
		glCullFace(GL_FRONT);
	}
	else
		glDisable(GL_CULL_FACE);
	
	
	
	if (x1->cullOrder.compare("ccw") == 0) {
		glFrontFace(GL_CCW);
	}else
		glFrontFace(GL_CW);

	//Lighting
	
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, x1->lightDoubleSided);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,x1->lightLocal);

	if(x1->lightEnabled)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, x1->lightAmbient);
}

void DemoScene::applyLights(){
	for(OmniLight *o1 : x1->omniLightVec){
		if(o1->getMarker())
			o1->draw();
	}

	for(SpotLight *spot1 : x1->spotLightVec){
		if(spot1->getMarker())
			spot1->draw();
	}
}

void DemoScene::drawScene(Node *node){
	
	glMultMatrixf(node->getTransformationMatrix());
	
	if (node->getPrimitives().size() != NULL) {
		node->getAppearance()->apply();
		for(Primitives *prim : node->getPrimitives()){
			prim->draw();
		}
	}
	vector<Node *> nodeDescendants = node->getDescendants();
	for(Node *nDesc : nodeDescendants){
		glPushMatrix();
		drawScene(nDesc);
		glPopMatrix();
	}
}
void DemoScene::update(unsigned long t)
{
	shader->bind();
	shader->update(t/400.0);
	shader->unbind();
	
}
	
void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
		//LOAD CAMERA
	bool foundcam=false;
	for(PerspectiveCamera *p1 : x1->PerscamVec)
		if(p1->getEnabled()){
			CGFscene::activeCamera = p1;
			CGFapplication::activeApp->forceRefresh();
			foundcam=true;
			break;

		}

	if(!foundcam){
		for(OrthoCamera *o1 : x1->OrthocamVec)
			if(o1->getEnabled()){
				CGFscene::activeCamera = o1;
				CGFapplication::activeApp->forceRefresh();
				foundcam=true;
				break;
			}
	}
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Apply transformations corresponding to the camera position relative to the origin



	CGFscene::activeCamera->applyView();


	//materialAppearance->apply();
	drawScene(x1->sceneGraph->getRootNode());
	//materialAppearance->apply();
	//obj->draw();

	for(OmniLight *l : x1->omniLightVec){
		l->update();
		if(l->getMarker())
			l->draw();
	}
	for(SpotLight *l2 : x1->spotLightVec){
		l2->update();
		if(l2->getMarker())
			l2->draw();
	}
	// Draw (and update) light
	//light0->draw();

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	// Simple object
	//materialAppearance->apply();
	//for( Node *n1 : x1->sceneGraph->getGraphNodes())
		//n1->draw();
	//obj->draw();
	//obj2->draw();
	//obj3->draw();
	//obj4->draw();
	
	// textured object
	
	//glTranslatef(0,4,0);
	//textureAppearance->apply();
	//obj->draw();

	// shader object

	//glTranslatef(0,4,0);
	//shader->bind();
	//obj->draw();
	


	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	//delete(light0);
}
