#include <gl\glew.h>
#include "Shader.h"	


Shader::Shader(CGFtexture *text, std::string vertexSPath, std::string fragmentSPath){
		init(vertexSPath.c_str(), fragmentSPath.c_str());
		CGFshader::bind();
		
		elapsedTime=0;
		this->text=text;
		imgLoc=glGetUniformLocation(id(),"img");
		windLoc=glGetUniformLocation(id(),"wind");
		tLoc=glGetUniformLocation(id(),"time");

		glUniform1i(imgLoc,0);

	}
	Shader::~Shader(){

	}
	void Shader::bind(float d, float w){
		CGFshader::bind();

		elapsedTime+=d/50;
		if(elapsedTime > FLT_MAX-1)
			elapsedTime=0;

		glUniform1f(tLoc,elapsedTime);
		glUniform1f(windLoc,w);
		glActiveTexture(GL_TEXTURE);
		text->apply();
		glActiveTexture(GL_TEXTURE0);

	}