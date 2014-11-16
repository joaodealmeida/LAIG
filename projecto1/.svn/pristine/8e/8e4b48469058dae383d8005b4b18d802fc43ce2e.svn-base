#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "CGF\CGFobject.h"
#include "Primitives.h"

class Rectangle: public CGFobject, public Primitives {
	public:
		Rectangle(float x1, float y1, float x2, float y2){
			this->x1=x1;
			this->y1=y1;
			this->x2=x2;
			this->y2=y2;
		}

		void draw(){
			glPushMatrix();
				float width = abs(x2 - x1);
				float height = abs(y2-y1);

				glTranslatef(x1,y1,0);
				glScalef(width,height,1);

				glBegin(GL_QUADS);
						glTexCoord2d(0, 0);
						glVertex2d(0, 0);
                
						glTexCoord2d(1, 0);
						glVertex2d(1, 0);
                
						glTexCoord2d(1, 1);
						glVertex2d(1, 1);
                
						glTexCoord2d(0, 1);
						glVertex2d(0, 1);
				glEnd();
			glPopMatrix();
		}

	private:
		float x1,y1,x2,y2;
};

#endif