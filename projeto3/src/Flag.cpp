#include <GL\glew.h>
#include "Flag.h"

Flag::Flag(GLenum drawstyle, GLenum normal, Texture *text) : Primitives(drawstyle, normal){
		this->text=text;
		plane=new Plane(drawstyle,normal,10);
		shader=nullptr;
		tHold=15;
		wind=0;
	}

void Flag::draw(){
		if(tHold){
			tHold--;
			return;
		}
		glPushMatrix();
			if(shader == nullptr)
				shader= new Shader(text,"data\\texshader.vert","data\\texshader.frag");
			
			shader->bind(0.05, wind);
			glActiveTexture(GL_TEXTURE0);
			text->apply();
			//glRotatef(180,0,1,0);
			//glScalef(5,0.5,5);
			plane->draw();
			shader->unbind();
		glPopMatrix();
	}
void Flag::setWind(int w){
		wind = w;
	}

int Flag::getWind(){
	return wind;
}

