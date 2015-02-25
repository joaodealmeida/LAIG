#ifndef LINEARANIMATION_H
#define LINEARANIMATION_H

#define M_PI 3.14159265358979323846264338327950288

#include "Animation.h"

class LinearAnimation : public Animation
{
private:
	float distance;
	std::vector<float> controlX;
	std::vector<float> controlY;
	std::vector<float> controlZ;

public:
	LinearAnimation(bool repeatable, std::string id, std::vector<float> controlX, std::vector<float> controlY, std::vector<float> controlZ, float span) : Animation(repeatable, id, span){
		
		for (int i = 0; i < controlX.size(); i++){
			this->controlX.push_back(controlX[i]);
			this->controlY.push_back(controlY[i]);
			this->controlZ.push_back(controlZ[i]);
		}
		this->previousPoint = 0;
		this->distance = 0;

		//Calculate Distance
		for (int i = 1; i < controlX.size(); i++) {
			this->distance += sqrtf( pow(controlX[i]-controlX[i-1],2) + pow(controlY[i]-controlY[i-1],2) + pow(controlZ[i]-controlZ[i-1],2));
		}
		
	}
	~LinearAnimation(){}

	void init(unsigned long t){
		if (controlX.size() > 0 && controlY.size() > 0 && controlZ.size() > 0) {
			xTrans = controlX[0];
			yTrans = controlY[0];
			zTrans = controlZ[0];
		}
		else {
			xTrans = yTrans = zTrans = 0;
		}
		startTime = t;
		reset = false;
		previousPoint = 0;
	}

	void update(unsigned long t){

		if (this->reset){
			printf("Entrou na animacao: %s\n", this->id);
			this->init(t);
			return;
		}
		unsigned long elapsedTime = t - this->startTime;
		startTime = t; //we can update startime now

		//Passar para o proximo ponto de controlo
		if ((previousPoint < controlX.size() - 1) && (xTrans == controlX[previousPoint + 1]) && (yTrans == controlY[previousPoint + 1]) && (zTrans == controlZ[previousPoint + 1]))
			previousPoint++;

		if (previousPoint == controlX.size() - 1) {
			if (repeatable)
				this->reset = true;
			
			waiting=false;
			return;
		}

		//Calculo do vetor movimento
		float pos[3];

		pos[0] = controlX[previousPoint + 1] - controlX[previousPoint];
		pos[1] = controlY[previousPoint + 1] - controlY[previousPoint];
		pos[2] = controlZ[previousPoint + 1] - controlZ[previousPoint];

		//Meter vetor movimento unitario

		float posUNIT = sqrtf(pow(pos[0], 2) + pow(pos[1], 2) + pow(pos[2], 2));

		if (posUNIT != 0)
		for (int i = 0; i < 3; i++)
			pos[i] /= posUNIT;

		//Velocidade

		float v = (distance / (span * 1000)) * elapsedTime;

		//Calcular Vetor Movimento 

		for (int i = 0; i < 3; i++)
			pos[i] *= v;

		//Adicionar valor as translacoes

		xTrans += pos[0];
		yTrans += pos[1];
		zTrans += pos[2];

		//Verificar se nao passou ao proximo ponto de controlo
		if ((pos[0] > 0 && xTrans > controlX[previousPoint + 1]) || (pos[0] < 0 && xTrans < controlX[previousPoint + 1]))
			xTrans = controlX[previousPoint + 1];

		if ((pos[1] > 0 && yTrans > controlY[previousPoint + 1]) || (pos[1] < 0 && yTrans < controlY[previousPoint + 1]))
			yTrans = controlY[previousPoint + 1];

		if ((pos[2] > 0 && zTrans > controlZ[previousPoint + 1]) || (pos[2] < 0 && zTrans < controlZ[previousPoint + 1]))
			zTrans = controlZ[previousPoint + 1];

		//Calcular angulo de rotacao

		float movXY[2], movZ[2];

		if (previousPoint + 1 < controlX.size()){
			float scalar, n1, n2;

			movXY[0] = controlX[previousPoint + 1] - controlX[previousPoint];
			movXY[1] = controlZ[previousPoint + 1] - controlZ[previousPoint];
			movZ[0] = 0;
			movZ[1] = 1;

			scalar = movXY[0] * movZ[0] + movXY[1] * movZ[1];
			n1 = sqrt(pow(movXY[0], 2.0f) + pow(movXY[1], 2.0f));
			n2 = sqrt(pow(movZ[0], 2.0f) + pow(movZ[1], 2.0f));
			rotation = acos(scalar / (n1*n2)) * (180 / M_PI);
			
		}
	}
	
	void apply(){
		glTranslatef(xTrans, yTrans, zTrans);
		glRotatef(rotation, 0, 1, 0);
	}

	void setWaiting(bool opt){
		this->waiting=opt;
	}
	bool getWaiting(){
		return waiting;
	}


	unsigned long startTime;
	unsigned int previousPoint;
};
#endif