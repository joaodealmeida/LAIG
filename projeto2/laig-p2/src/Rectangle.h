#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "CGF\CGFobject.h"
#include "Primitives.h"

class Rectangle: public CGFobject, public Primitives {
	public:
		Rectangle(GLenum drawstyle, GLenum normal,float x1, float y1, float x2, float y2) : Primitives(drawstyle, normal){
			this->x1=x1;
			this->y1=y1;
			this->x2=x2;
			this->y2=y2;
		}

		void setDrawStyle(GLenum newstyle){
			style=newstyle;
		}

		void draw(){
				
			    if(style == GLU_LINE) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
				if(style == GLU_FILL) glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
				if(style == GLU_POINT) glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );



				glPushMatrix();
				glBegin(GL_QUADS);
					glNormal3f(0,0,1);
					glTexCoord2d(0,0);
					glVertex3f(x1, y1, 0);
    
					glTexCoord2d(1, 0);
					glVertex3f(x2, y1, 0);
    
					glTexCoord2d(1, 1);
					glVertex3f(x2, y2, 0);
    
					glTexCoord2d(0, 1);
					glVertex3f(x1, y2, 0);
    
				glEnd();
				
				glPopMatrix();
		}

	private:
		float x1,y1,x2,y2;
		GLenum style;
};

#endif