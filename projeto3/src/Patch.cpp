#include "Patch.h"
#include <GL/glut.h>


// DECLARACOES RELACIONADAS COM OS "EVALUATORS"
//   atenção à ordem dos pontos que nao e' circular...
// Coordenadas dos 4 pontos de controlo (podem ser entendidas como
//   sendo as coordenadas dos cantos do polígono a visualizar):


const GLfloat Patch::normalComponent[4][3] = { { 0.0, 0.0, 1.0 },
{ 0.0, 0.0, 1.0 },
{ 0.0, 0.0, 1.0 },
{ 0.0, 0.0, 1.0 } };

// As cores a atribuir a cada ponto de controlo:
//   Nota: para uma boa percepcao do efeito de iluminacao, é
//         aconselhável usar, em alternativa, uma cor cinzenta
/*const GLfloat Patch::colorPoints[4][4] = { { 0.0, 0.7, 0.7, 0 },
{ 0.0, 0.0, 0.7, 0 },
{ 0.0, 0.7, 0.0, 0 },
{ 0.7, 0.0, 0.0, 0 } };
*/


Patch::Patch(GLenum drawstyle, GLenum normal, int order, int partsU, int partsV, std::string compute, GLfloat *controlPoints) : Primitives(drawstyle, normal)
{
	this->order = order;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
	int size = (order + 1)*(order + 1)*3;
	

	//Numero de pontos sempre -> (ordem+1^)^2
	this->controlPoints = new GLfloat[size];

	for (int i = 0; i < (order + 1)*(order + 1); i++) {
		this->controlPoints[i * 3 + 0] = controlPoints[i * 3 + 0];
		this->controlPoints[i * 3 + 1] = controlPoints[i * 3 + 1];
		this->controlPoints[i * 3 + 2] = controlPoints[i * 3 + 2];
	}
	std::vector<float> temp;
	for(int i=0; i<(order + 1)*(order + 1)*3;i++)
		temp.push_back(this->controlPoints[i]);

	for (int i = (order + 1)*(order + 1), j=0; i<0;i--,j++)
		this->controlPoints[j]= temp[i];

	
	//calcTextPoints(this->order);

	

	//myTexture = new CGFtexture("../data/evaltext.jpg");
}

/*void Patch::calcTextPoints(int order){
	
	if (order == 1){
		GLfloat temp[4][2] = {
							  { 0.0, 1 }, 
							  { 1, 1 },
							  { 0.0, 0.0 },
						      { 1, 0.0 }
							};
		
		texturePoints = *temp;
	}else if (order == 2){
		GLfloat temp[9][2] = { { 0.0, 1 }, { 0.5, 1 },
							   { 1, 1 },{ 0.0, 0.5 }, 
							   { 0.5, 0.5 }, { 1, 0.5 },
							   { 0.0, 0.0 }, { 0.5, 0.0 },
							   { 1, 0.0 } 
							 };
		
		texturePoints = *temp;
	}
	else if (order == 3){
		GLfloat temp[16][2] = { { 0.0, 1 }, { 1/3, 1 }, { 2 / 3, 1 }, { 1, 1 },
								{ 0.0, 2/3 }, { 1/3, 2/3 }, { 2/3, 2/3 }, { 1, 2/3 },
								{ 0.0, 1/3 }, { 1/3, 1/3 }, { 2/3, 1/3 }, { 1, 1/3 },
								{ 0.0, 0.0 }, { 1/3, 0.0 }, { 2/3, 0.0 }, { 1, 0.0 }
							  };
		texturePoints = new GLfloat[16*2];
		texturePoints = *temp;
	}

}*/
Patch::~Patch()
{
	//delete(myTexture);
}

void Patch::setDrawStyle(GLenum newstyle){
		if(newstyle == GL_FILL)
			compute="fill";
		else if (newstyle == GL_LINE)
			compute="line";
		else if (newstyle == GL_POINT)
			compute = "point";
	}

void Patch::draw(void)
{
	glEnable(GL_AUTO_NORMAL);
	//CALCULO PONTOS DE TEXTURA
	GLfloat *texturePoints;

	if (order == 1){
		GLfloat temp[4][2] = {
							  { 0.0, 1 }, 
							  { 1, 1 },
							  { 0.0, 0.0 },
						      { 1, 0.0 }
							};
		
		texturePoints = *temp;
	}else if (order == 2){
		GLfloat temp[9][2] = { { 0.0, 1 }, { 0.5, 1 },
							   { 1, 1 },{ 0.0, 0.5 }, 
							   { 0.5, 0.5 }, { 1, 0.5 },
							   { 0.0, 0.0 }, { 0.5, 0.0 },
							   { 1, 0.0 } 
							 };
		
		texturePoints = *temp;
	}
	else if (order == 3){
		GLfloat temp[16][2] = { { 0.0, 1 }, { 1/3, 1 }, { 2 / 3, 1 }, { 1, 1 },
								{ 0.0, 2/3 }, { 1/3, 2/3 }, { 2/3, 2/3 }, { 1, 2/3 },
								{ 0.0, 1/3 }, { 1/3, 1/3 }, { 2/3, 1/3 }, { 1, 1/3 },
								{ 0.0, 0.0 }, { 1/3, 0.0 }, { 2/3, 0.0 }, { 1, 0.0 }
							  };
		texturePoints = new GLfloat[16*2];
		texturePoints = *temp;
	}

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order+1,  0.0, 1.0, 3*(order+1), order+1,  &controlPoints[0]);
	//glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	//glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, order+1,  0.0, 1.0, (order+1)*2, order+1,  &texturePoints[0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	//glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	// para este conjunto de interpoladores:
	//    na direccao U, serao efectuadas divisoes em 40 passos
	//        quando a variável U varia de 0 a 1
	//    na direccao V, serao efectuadas divisoes em 60 passos
	//        quando a variável U varia de 0 a 1
	glMapGrid2f(this->partsU, 0.0,1.0, this->partsV, 0.0,1.0); 

	
	// SEGUE-SE EXEMPLO DE UTILIZACAO DE "EVALUATORS"
	//glShadeModel(GL_SMOOTH);					// GL_FLAT, GL_SMOOTH
	//glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_TEXTURE_2D);
	//myTexture->apply();


	glEvalMesh2(compute == "fill" ? GL_FILL : compute == "line" ? GL_LINE : GL_POINT, 0,this->partsU, 0,this->partsV);		// GL_POINT, GL_LINE, GL_FILL
	//glEvalMesh2(GL_FILL, 10,30, 20,40);	// poligono incompleto...
	//glEvalMesh2(GL_FILL, -10,50, -20,70);	// ...ou "transbordante"
	// NOTA: os 4 ultimos parametros da funcao glEvalMesh2() nao sao 
	//		 coordenadas mas sim indices de passos (do passo -10
	//		 ao passo 50; do passo -20 ao passo 70...

	// so' para referencia visual... onde estao os quatro pontos
	// de controlo:


	

	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_AUTO_NORMAL);


}