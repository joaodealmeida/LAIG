#ifndef VEHICLE_H
#define VEHICLE_H

#include <cmath>
#include "CGF\CGFobject.h"
#include "Primitives.h"
#include "Plane.h"
#include "Patch.h"

class Vehicle : public CGFobject, public Primitives {
private:
	GLenum style;
	Patch *patch;
	Plane *plane;
	Rectangle *rectangle;
	Triangle *triangle;
	GLfloat controlPoints[16][3];


public:
	

	Vehicle(GLenum drawstyle, GLenum normal) : Primitives(drawstyle, normal){
		plane = new Plane(drawstyle, normal, 10);
		rectangle = new Rectangle(drawstyle, normal, 0, 0, 1.5, 1.5);
		triangle = new Triangle(drawstyle, normal, 0, -0.5, 0, 1, -0.5, 0, 0.5, 0.5, 0);
		//Pontos de controlo para PATCH
		GLfloat controlPoints[16][3] = {
				{ -0.5, 0, -0.5 },
				{ -0.5, 0, -0.25 },
				{ -0.5, 0, 0.25 },
				{ -0.5, 0, 0.5 },
				{ -0.25, 0, -0.5 },
				{ -0.25, 1, -0.25 },
				{ -0.25, 1, 0.25 },
				{ -0.25, 0, 0.5 },
				{ 0.25, 0, -0.5 },
				{ 0.25, 1, -0.25 },
				{ 0.25, 1, 0.25 },
				{ 0.25, 0, 0.5 },
				{ 0.5, 0, -0.5 },
				{ 0.5, 0, -0.25 },
				{ 0.5, 0, 0.25 },
				{ 0.5, 0, 0.5 } };
		//
		patch = new Patch(drawstyle, normal, 3, 10, 10, "fill", controlPoints[0]);
	}
	~Vehicle(){}

	void setDrawStyle(GLenum newstyle){
		style = newstyle;
	}

	void draw(){

		/*if (style == GLU_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (style == GLU_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (style == GLU_POINT) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);*/
		//Cobertura cima
		glPushMatrix();
			glTranslatef(0, 1, 0);
			patch->draw();
		glPopMatrix();

		//Cobertura baixo
		glPushMatrix();
			glTranslatef(0, -1, 0);
			glRotatef(180, 1, 0, 0);
			plane->draw();
		glPopMatrix();

		//Lateral esquerda
		glPushMatrix();
			glTranslatef(-1, 0, 0);
			glRotatef(90, 0, 0, 1);
			plane->draw();
		glPopMatrix();


		//Asa direita
		glPushMatrix();
		glTranslatef(0, 0, 1);
		glRotatef(90, 1, 0, 0);
			triangle->draw();
		glPopMatrix();
		
		//Frente
		glPushMatrix();
			glTranslatef(-1, -1, 0.5);
			rectangle->draw();
		glPopMatrix();

		//Tras
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(-0.5, -1, 0.5);
			rectangle->draw();
		glPopMatrix();




		

		



	}

};

#endif