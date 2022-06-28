
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
//#include <GL\freeGlut.h>
#include "RgbImage.h"

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes
GLfloat tam = 0.8;
GLfloat tamx = 0.4;
GLfloat tamy = 0.4;
GLfloat tamz = 0.4;

static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam, -tam,	// 0 
		-tam,  -tam,  tam,	// 1 
		-tam,   tam,  tam,	// 2 
		-tam,   tam, -tam,	// 3 

	//…………………………………………………… Direita
		 tam,  -tam,  tam,	// 4 
		 tam,  -tam, -tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,   tam,  tam,	// 7  
	//……………………………………………………… (Cima
		-tam,  tam,  tam,	// 8 
		 tam,  tam,  tam,	// 9
		 tam,  tam, -tam,	// 10 
		-tam,  tam, -tam,	// 11 
		//……………………………………………………… (baixo
		-tam,  -tam, -tam,	// 12 
		 tam,  -tam, -tam,	// 13
		 tam,  -tam,  tam,	// 14 
		-tam,  -tam,  tam,	// 15 
		//……………………………………………………… (frente
		-tam,  -tam,  tam,	// 16 
		 tam,  -tam,  tam,	// 17
		 tam,   tam,  tam,	// 18 
		-tam,   tam,  tam,	// 19 
		//……………………………………………………… (traz
		 tam,  -tam, -tam,	// 20 
		-tam,  -tam, -tam,	// 21
		-tam,   tam, -tam,	// 22 
		 tam,   tam, -tam,	// 23 
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   //…………………………………………………………………………………………………… y=tam (baixo)
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   //…………………………………………………………………………………………………… z=tam (frente)
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   //…………………………………………………………………………………………………… z=tam (traz)
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
};

//------------------------------------------------------------ Cores
static GLfloat cor[] = {
	//…………………………………………………………………………………………………… (Esquerda)
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  1.0,  0.0,
	  1.0,  1.0,  0.0,
	  //…………………………………………………………………………………………………… (Direita)
		0.0,  0.0,  1.0,
		1.0,  0.0,  1.0,
		1.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//…………………………………………………………………………………………………… (Cima)
		0.0,  1.0,  1.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  1.0,
		//…………………………………………………………………………………………………… (baixo)
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  1.0,  0.0,
	  1.0,  1.0,  0.0,
	  //…………………………………………………………………………………………………… (frente)
		0.0,  0.0,  1.0,
		1.0,  0.0,  1.0,
		1.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		//…………………………………………………………………………………………………… (traz)
		0.0,  1.0,  1.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  1.0,
};


static GLfloat texturas[] = {
0, 0,
tamz, 0,
tamz, tamy,
0, tamy,

0, 0,
tamz, 0,
tamz, tamy,
0, tamy,

0, 0,
tamx, 0,
tamx, tamz,
0, tamz,

0, 0,
tamx, 0,
tamx, tamz,
0, tamz,

0, 0,
tamx, 0,
tamx, tamy,
0, tamy,

0, 0,
tamx, 0,
tamx, tamy,
0, tamy };

//=========================================================== FACES DA MESA
GLboolean   frenteVisivel = 1;
static GLuint     cima[] = { 8, 9, 10, 11 };   // regra da mao direita
static GLuint     esquerda[] = { 0, 1, 2,  3 };
static GLuint     direita[] = { 4, 5, 6,  7 };
static GLuint     baixo[] = { 12, 13, 14,  15 };
static GLuint     frente[] = { 16, 17, 18,  19 };
static GLuint     traz[] = { 20, 21, 22, 23 };

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 1200, hScreen = 900;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 15.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, aVisao2 = 0, incVisao = 0.05;
GLfloat  rVisaoL = 10, aVisaoL = -0.5 * PI, aVisao2L = 0, incVisaoL = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao2) * cos(aVisao), rVisao * sin(aVisao2) + 2 * tam, rVisao * cos(aVisao2) * sin(aVisao) };
GLfloat obsL[] = { rVisaoL * cos(aVisao2L) * cos(aVisaoL), rVisaoL * sin(aVisao2L), rVisaoL * cos(aVisao2L) * sin(aVisaoL) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;
//--------------------------------------------------------------
bool Door1_up = false;
bool Door1_down = false;
GLfloat  angulo1 = 0;
GLfloat  trans = 0;
GLfloat  aux = 0;
GLfloat  t_button = 0;
bool Door2_open = false;
bool Door2_close = false;
bool open = false;
GLfloat  angulo2 = 0;
GLfloat  angulo3 = 0;

bool subir = false;
bool descer = false;

bool UP = false;
bool DOWN = false;
bool LEFT = false;
bool RIGHT = false;
bool look = false;
//--------------------------------------------------------------------
//texturas
GLuint   texture[7];
RgbImage imag;
//

//luz
float PosicaoDir[4] = { 0,5,3,0 };
float CorAmbDir[4] = { 0, 0, 0, 1 };
float CorDifDir[4] = { 1, 1, 1, 1 };
float CorEspDir[4] = { 1, 1, 1, 1 };
bool AumentaLuzDir = false;
int LuzDir = 1;

float PosicaoPont1[4] = { (-7+0.4) * tam, 1 * tam ,3 * tam, 1 };
float PosicaoPont2[4] = { (7-0.4) * tam, 1 * tam ,3 * tam, 1 };
float CorAmbPont[4] = { 0, 0, 0, 1 };
float CorDifPont[4] = { 1, 0, 0, 1 };
float CorEspPont[4] = { 1, 0, 0, 1 };
bool DiminuiLuzDir = false;

float luzGlobalCor[3] = { 0.4, 0.4, 0.4 };

GLfloat localAttCon = 1;
//

//Materiais
GLfloat  tinAmb[] = { 0.105882, 0.058824, 0.113725 };
GLfloat  tinDif[] = { 0.427451, 0.470588, 0.541176 };
GLfloat  tinSpec[] = { 0.333333, 0.333333, 0.521569 };
GLint    tinCoef = 9.84615;

GLfloat  pSilverAmb[] = { 0.23125, 0.23125, 0.23125 };
GLfloat  pSilverDif[] = { 0.2775, 0.2775, 0.2775 };
GLfloat  pSilverSpec[] = { 0.773911, 0.773911, 0.773911 };
GLint   pSilverCoef = 89.6;

GLfloat  obsidianAmb[] = { 0.05375 ,0.05 ,0.06625 };
GLfloat  obsidianDif[] = { 0.18275 ,0.17 ,0.22525 };
GLfloat  obsidianSpec[] = { 0.332741 ,0.328634 ,0.346435 };
GLint  obsidianCoef = 0.3 * 128;

GLfloat  pearlAmb[] = { 0.25 ,0.20725 ,0.20725 };
GLfloat  pearlDif[] = { 1.0 ,0.829 ,0.829 };
GLfloat  pearlSpec[] = { 0.296648 ,0.296648 ,0.296648 };
GLint  pearlCoef = 0.088 * 128;

GLfloat  rubyAmb[] = { 0.1745 ,0.01175 ,0.01175 };
GLfloat  rubyDif[] = { 0.61424 ,0.04136 ,0.04136 };
GLfloat  rubySpec[] = { 0.727811 ,0.626959 ,0.626959 };
GLint  rubyCoef = 0.6 * 128;

GLfloat  GlassAmb[] = { 0.8 ,0.8 ,0.8, 1 };
GLfloat  GlassDif[] = { 0.55 ,0.55 ,0.55, 0.4 };
GLfloat  GlassSpec[] = { 0.870 ,0.870 ,0.870, 1 };
GLint  Glass2Coef = 128;

GLfloat  Glass2Amb[] = { 0.8 ,0.8 ,0.8, 1 };
GLfloat  Glass2Dif[] = { 0.55 ,0.55 ,0.55, 0.8 };
GLfloat  Glass2Spec[] = { 0.870 ,0.870 ,0.870, 1 };
GLint  GlassCoef = 128;

GLfloat  bronzeAmb[] = { 0.2125 ,0.1275 ,0.054 };
GLfloat  bronzeDif[] = { 0.714 ,0.4284 ,0.18144 };
GLfloat  bronzeSpec[] = { 0.393548 ,0.271906 ,0.166721 };
GLint  bronzeCoef = 0.2 * 128;

GLfloat  chromeAmb[] = { 0.25 ,0.25 ,0.25 };
GLfloat  chromeDif[] = { 0.4 ,0.4 ,0.4 };
GLfloat  chromeSpec[] = { 0.774597 ,0.774597 ,0.774597 };
GLint  chromeCoef = 0.6 * 128;

GLfloat  copperAmb[] = { 0.19125 ,0.0735 ,0.0225 };
GLfloat  copperDif[] = { 0.7038 ,0.27048 ,0.0828 };
GLfloat  copperSpec[] = { 0.256777 ,0.137622 ,0.086014 };
GLint  copperCoef = 0.1 * 128;

GLfloat  goldAmb[] = { 0.24725 ,0.1995 ,0.0745 };
GLfloat  goldDif[] = { 0.75164 ,0.60648 ,0.22648 };
GLfloat  goldSpec[] = { 0.628281 ,0.555802 ,0.366065 };
GLint  goldCoef = 0.4 * 128;

GLfloat  silverAmb[] = { 0.19225 ,0.19225 ,0.19225 };
GLfloat  silverDif[] = { 0.50754 ,0.50754 ,0.50754 };
GLfloat  silverSpec[] = { 0.508273 ,0.508273 ,0.508273 };
GLint  silverCoef = 0.4 * 128;

GLfloat blackPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
GLfloat blackPlasticDif[] = { 0.00 ,0.00 ,0.00 };
GLfloat blackPlasticSpec[] = { 0.0 ,0.00 ,0.0 };
GLint blackPlasticCoef = 0.25 * 128;

GLfloat  cyanPlasticAmb[] = { 0.0 ,0.1 ,0.06 };
GLfloat  cyanPlasticDif[] = { 0.0 ,0.50980392 ,0.50980392 };
GLfloat  cyanPlasticSpec[] = { 0.0 ,0.50196078 ,0.50196078 };
GLint  cyanPlasticCoef = 0.25 * 128;

GLfloat greenPlasticAmb[] = { 0.0 ,0.2 ,0.0 };
GLfloat greenPlasticDif[] = { 0.0 ,0.35 ,0.0 };
GLfloat greenPlasticSpec[] = { 0.0 ,0.55 ,0.0 };
GLint greenPlasticCoef = 0.25 * 128;

GLfloat  redPlasticAmb[] = { 0.2 ,0.0 ,0.0 };
GLfloat  redPlasticDif[] = { 0.5 ,0.0 ,0.0 };
GLfloat  redPlasticSpec[] = { 0.7 ,0.0 ,0.0 };
GLint  redPlasticCoef = 0.25 * 128;

GLfloat whitePlasticAmb[] = { 0.8 ,0.8 ,0.8 };
GLfloat whitePlasticDif[] = { 0.55 ,0.55 ,0.55 };
GLfloat whitePlasticSpec[] = { 0.870 ,0.870 ,0.870 };
GLint whitePlasticCoef = 0.25 * 128;

GLfloat pedraAmb[] = { 0.8 ,0.8 ,0.8 };
GLfloat pedraDif[] = { 0.55 ,0.55 ,0.55 };
GLfloat pedraSpec[] = { 0.870 ,0.870 ,0.870 };
GLint pedraCoef = 0.25 * 128;

GLfloat wmAmb[] = { 0.8 ,0.8 ,0.8 };
GLfloat wmDif[] = { 0.55 ,0.55 ,0.55 };
GLfloat wmSpec[] = { 0.870 ,0.870 ,0.870 };
GLint wmCoef = 0.25*128;
//

void initTexturas()
{
	//----------------------------------------- Parede
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("pedra.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//----------------------------------------- PortaGaragem
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("portaGaragem3.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("sky.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("relva.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("noite.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	imag.LoadBmpFile("estrada.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[6]);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	imag.LoadBmpFile("passeio.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);

	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, PosicaoDir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, CorAmbDir);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, CorDifDir);
	glLightfv(GL_LIGHT0, GL_SPECULAR, CorEspDir);
	
	/*
	float pos[] = { obsP[0], obsP[1], obsP[2], 1 };
	float dir[] = { obsL[0] - obsP[0], obsL[1] - obsP[1], obsL[2] - obsP[2], 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, CorDifPont);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	*/
	
	glLightfv(GL_LIGHT2, GL_POSITION, PosicaoPont1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, CorAmbPont);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, CorDifPont);
	glLightfv(GL_LIGHT2, GL_SPECULAR, CorEspPont);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05);
	
	
	glLightfv(GL_LIGHT3, GL_POSITION, PosicaoPont2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, CorAmbPont);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, CorDifPont);
	glLightfv(GL_LIGHT3, GL_SPECULAR, CorEspPont);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.05);
	
}


void initMaterials(int material) {

	switch (material) {
	case 0: //……………………………………………………………………………………………Tin
		glMaterialfv(GL_FRONT, GL_AMBIENT, tinAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, tinDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, tinSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, tinCoef);
		break;
	case 1: //……………………………………………………………………………………………pSilver
		glMaterialfv(GL_FRONT, GL_AMBIENT, pSilverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pSilverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pSilverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pSilverCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………glass
		glMaterialfv(GL_FRONT, GL_AMBIENT, GlassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GlassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, GlassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, GlassCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, Glass2Amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Glass2Dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Glass2Spec);
		glMaterialf(GL_FRONT, GL_SHININESS, Glass2Coef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, wmAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, wmDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, wmSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, wmCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………whitePlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………Pedra
		glMaterialfv(GL_FRONT, GL_AMBIENT, pedraAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pedraDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pedraSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pedraCoef);
		break;
	case 18: //……………………………………………………………………………………………Pedra
		float cor[] = { 1,1,1,1 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, cor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cor);
		glMaterialf(GL_FRONT, GL_SHININESS, 128);
		break;
	}
}

//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	initTexturas();
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	glEnable(GL_NORMALIZE);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glColorPointer(3, GL_FLOAT, 0, cor);
	//glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	float cor[] = { 1,1,1,0 };

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.020);
	glFogfv(GL_FOG_COLOR, cor);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	initLights();

	glEnable(GL_CULL_FACE);
}



void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

}

GLUquadricObj* bola = gluNewQuadric();

void drawchao() {
	float cor[] = { 1,1,1,1 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, cor);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(-15, 0, 15);

	glTexCoord2f(15-7.5*tam, 0);
	glVertex3d(-7.5*tam, 0, 15);

	glTexCoord2f(15-7.5*tam, 15);
	glVertex3d(-7.5*tam, 0, -15);

	glTexCoord2f(0, 15);
	glVertex3d(-15, 0, -15);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(-7.5 * tam, 0, 15);

	glTexCoord2f(1, 0);
	glVertex3d(-6 * tam, 0, 15);

	glTexCoord2f(1, 15);
	glVertex3d(-6 * tam, 0, -15);

	glTexCoord2f(0, 15);
	glVertex3d(-7.5 * tam, 0, -15);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(-6*tam, 0, 15);

	glTexCoord2f(6*tam, 0);
	glVertex3d(6*tam, 0, 15);

	glTexCoord2f(6*tam, 15);
	glVertex3d(6*tam, 0, -15);

	glTexCoord2f(0, 15);
	glVertex3d(-6*tam, 0, -15);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(6 * tam, 0, 15);

	glTexCoord2f(1, 0);
	glVertex3d(7.5 * tam, 0, 15);

	glTexCoord2f(1, 15);
	glVertex3d(7.5 * tam, 0, -15);

	glTexCoord2f(0, 15);
	glVertex3d(6 * tam, 0, -15);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3d(7.5*tam, 0, 15);

	glTexCoord2f(15-7.5*tam, 0);
	glVertex3d(15, 0, 15);

	glTexCoord2f(15-7.5*tam, 15);
	glVertex3d(15, 0, -15);

	glTexCoord2f(0, 15);
	glVertex3d(7.5*tam, 0, -15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
}

void drawBola()
{
		glCullFace(GL_FRONT);
	//------------------------- Bola
	
	if (LuzDir) {
		float cor[] = { 1,1,1,1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, cor);
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.025);
		glFogfv(GL_FOG_COLOR, cor);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
	}
	else {
		float cor[] = { 0.8,0.8,0.8,1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, cor);
		float cor2[] = { 0.1,0.1,0.1,1 };
		glFogi(GL_FOG_MODE, GL_EXP2);
		glFogf(GL_FOG_DENSITY, 0.060);
		glFogfv(GL_FOG_COLOR, cor2);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
	}
	glEnable(GL_TEXTURE_2D);
	initMaterials(18);
	glPushMatrix();
	glRotatef(20, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glRotatef(230, 0, 1, 0);
	gluQuadricDrawStyle(bola, GLU_FILL);
	gluQuadricNormals(bola, GLU_SMOOTH);
	gluQuadricTexture(bola, GL_TRUE);
	gluSphere(bola, 15.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
	glCullFace(GL_BACK);
}

void drawBola2()
{
	initMaterials(7);
	glPushMatrix();
	gluQuadricDrawStyle(bola, GLU_FILL);
	gluQuadricNormals(bola, GLU_SMOOTH);
	gluQuadricTexture(bola, GL_TRUE);
	gluSphere(bola, 0.3*tam, 100, 100);
	glPopMatrix();
}

void malha3(int textura, int material) {
	/*



		   -1.0,4.0______-1.0,4.0
				|			|
				|			|
				|			|
		   -1.0,-4.0      1.0,-4,0
	*/
	float tmax = 1 *0.4;
	float tamy = 4 *0.4;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[textura]);

	glPushMatrix();
	initMaterials(material);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (float i = -4; i < 4; i += 0.25)
		for (float j = -1; j < 1; j += 0.25) {
			glTexCoord2f((j + 1)/2 * tamx, (i + 4)/8 * tamy);
			glVertex3d(j * tam, i * tam, 0.5 * tam);

			glTexCoord2f((j + 1 + 0.25)/2 * tamx, (i + 4)/8 * tamy);
			glVertex3d((j + 0.25) * tam, i * tam, 0.5 * tam);

			glTexCoord2f((j + 1 + 0.25)/2 * tamx, (i + 4 + 0.25)/8 * tamy);
			glVertex3d((j + 0.25) * tam, (i + 0.25) * tam, 0.5 * tam);

			glTexCoord2f((j + 1)/2 * tamx, (i + 4 + 0.25)/8 * tamy);
			glVertex3d(j * tam, (i + 0.25) * tam, 0.5 * tam);

		}
	glEnd();
	/*
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);
	for (float i = -1.95; i < 1.95; i += 0.25)
		for (float j = -0.4; j < 0.4; j += 0.25) {

			glVertex3d((j + 0.1) * tam, i * tam, -0.25 * tam);

			glVertex3d(j * tam, i * tam, -0.1 * tam);

			glVertex3d(j * tam, (i + 0.1) * tam, -0.1 * tam);

			glVertex3d((j + 0.1) * tam, (i + 0.1) * tam, -0.1 * tam);

		}
	glEnd();
	*/
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void malha2(int material) {
	/*
	
														
														
		   -2.9,4.7______-2.1,4.7						
				|			|							
				|			|							
				|			|							
		   -2.9,0.8      -2.1,0.8
	*/

	glPushMatrix();
	initMaterials(material);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (float i = -1.95; i < 1.95; i += 0.1)
		for (float j = -0.4; j < 0.4; j += 0.1) {
				glVertex3d(j * tam, i * tam, 0.1 * tam);

				glVertex3d((j + 0.1) * tam, i * tam, 0.1 * tam);

				glVertex3d((j + 0.1) * tam, (i + 0.1) * tam, 0.1 * tam);

				glVertex3d(j * tam, (i + 0.1) * tam, 0.1 * tam);
			
		}
	glEnd();
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);
	for (float i = -1.95; i < 1.95; i += 0.1)
		for (float j = -0.4; j < 0.4; j += 0.1) {
			
			glVertex3d((j + 0.1) * tam, i * tam, -0.1 * tam);

			glVertex3d(j * tam, i * tam, -0.1 * tam);

			glVertex3d(j * tam, (i + 0.1) * tam, -0.1 * tam);

			glVertex3d((j + 0.1) * tam, (i + 0.1) * tam, -0.1 * tam);
			
		}
	glEnd();
	glPopMatrix();
}



void malha(int textura, int material) {
	/*
	-6.8______________________________________________6,8
	|													|
	|													|
	|	   -3.5,5.5______-0.5,5.5						|
	|			|			|							|
	|			|			|							|
	|			|			|							|
	-6,0___-3.5,0         -0.5,0______________________6,0
	*/


	float tmax = 0.2;
	float tamy = 0.2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[textura]);
	glPushMatrix();
	initMaterials(material);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (float i = 0; i < 8; i += 0.25)
		for (float j = -6; j < 6; j += 0.25) {
			if (j >= -3.5 && j < -0.5 && i < 5.5) {}
			else {
				glTexCoord2f(j * tamx, i * tamy);
				glVertex3d(j * tam, i * tam, 0.25 * tam);

				glTexCoord2f((j + 0.25) * tamx, i * tamy);
				glVertex3d((j + 0.25) * tam, i * tam, 0.25 * tam);

				glTexCoord2f((j + 0.25) * tamx, (i + 0.25) * tamy);
				glVertex3d((j + 0.25) * tam, (i + 0.25) * tam, 0.25 * tam);

				glTexCoord2f(j * tamx, (i + 0.25) * tamy);
				glVertex3d(j * tam, (i + 0.25) * tam, 0.25 * tam);
			}
		}
	glEnd();
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);
	for (float i = 0; i < 8; i += 0.25)
		for (float j = -6; j < 6; j += 0.25) {
			if (j >= -3.5 && j < -0.5 && i < 5.5) {}
			else {

				glTexCoord2f((j + 0.25) * tamx, i * tamy);
				glVertex3d((j + 0.25) * tam, i * tam, -0.25 * tam);

				glTexCoord2f(j * tamx, i * tamy);
				glVertex3d(j * tam, i * tam, -0.25 * tam);

				glTexCoord2f(j * tamx, (i + 0.25) * tamy);
				glVertex3d(j * tam, (i + 0.25) * tam, -0.25 * tam);

				glTexCoord2f((j + 0.25) * tamx, (i + 0.25) * tamy);
				glVertex3d((j + 0.25) * tam, (i + 0.25) * tam, -0.25 * tam);
				
			}
		}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawCub() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, traz);
}

void drawCub2() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
}

void drawCub3() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, traz);
}

void drawCubWithMaterial(int material) {
	glPushMatrix();
	initMaterials(material);
	drawCub();
	glPopMatrix();
}

void drawCubWithMaterial2(int material) {
	glPushMatrix();
	initMaterials(material);
	drawCub2();
	glPopMatrix();
}

void drawCubWithMaterial3(int material) {
	glPushMatrix();
	initMaterials(material);
	drawCub3();
	glPopMatrix();
}

void drawCubWithTexture(GLfloat x, GLfloat y, GLfloat z, int material, int textura) {
	texturas[18] = x * tamx;
	texturas[20] = x * tamx;
	texturas[26] = x * tamx;
	texturas[28] = x * tamx;
	texturas[34] = x * tamx;
	texturas[36] = x * tamx;
	texturas[42] = x * tamx;
	texturas[44] = x * tamx;

	texturas[5] = y * tamy;
	texturas[7] = y * tamy;
	texturas[13] = y * tamy;
	texturas[15] = y * tamy;
	texturas[37] = y * tamy;
	texturas[39] = y * tamy;
	texturas[45] = y * tamy;
	texturas[47] = y * tamy;

	texturas[2] = z * tamz;
	texturas[4] = z * tamz;
	texturas[10] = z * tamz;
	texturas[12] = z * tamz;
	texturas[21] = z * tamz;
	texturas[23] = z * tamz;
	texturas[29] = z * tamz;
	texturas[31] = z * tamz;

	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[textura]);

	drawCubWithMaterial(material);

	glDisable(GL_TEXTURE_2D);
}

void drawCubWithTexture3(GLfloat x, GLfloat y, GLfloat z, int material, int textura) {
	texturas[18] = x * tamx;
	texturas[20] = x * tamx;
	texturas[26] = x * tamx;
	texturas[28] = x * tamx;
	texturas[34] = x * tamx;
	texturas[36] = x * tamx;
	texturas[42] = x * tamx;
	texturas[44] = x * tamx;

	texturas[5] = y * tamy;
	texturas[7] = y * tamy;
	texturas[13] = y * tamy;
	texturas[15] = y * tamy;
	texturas[37] = y * tamy;
	texturas[39] = y * tamy;
	texturas[45] = y * tamy;
	texturas[47] = y * tamy;

	texturas[2] = z * tamz;
	texturas[4] = z * tamz;
	texturas[10] = z * tamz;
	texturas[12] = z * tamz;
	texturas[21] = z * tamz;
	texturas[23] = z * tamz;
	texturas[29] = z * tamz;
	texturas[31] = z * tamz;

	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[textura]);

	drawCubWithMaterial3(material);

	glDisable(GL_TEXTURE_2D);
}

void drawCandeeiro(int x) {
	glPushMatrix();
	glTranslatef(x*(7 - 0.25) * tam, 1 * tam, 3 * tam);

	glPushMatrix();
	glTranslatef(-0.3 * tam, 0, 0.3 * tam);
	glScalef(0.05, 0.2, 0.05);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * tam, 0, 0.3 * tam);
	glScalef(0.05, 0.2, 0.05);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3 * tam, 0, -0.3 * tam);
	glScalef(0.05, 0.2, 0.05);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3 * tam, 0, -0.3 * tam);
	glScalef(0.05, 0.2, 0.05);
	drawCubWithMaterial(2);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, (-0.07 - 0.2) * tam, 0);
	glScalef(0.4, 0.07, 0.4);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (-0.21 - 0.2) * tam, 0);
	glScalef(0.3, 0.07, 0.3);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (-0.21 - 0.2 - 1) * tam, 0);
	glScalef(0.07, 1.0, 0.07);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (0.07 + 0.2) * tam, 0);
	glScalef(0.4, 0.07, 0.4);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (0.14 + 0.2) * tam, 0);
	glScalef(0.3, 0.07, 0.3);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	if (CorDifPont[0] || CorDifPont[1] || CorDifPont[2])glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CorDifPont);
	glScalef(0.3, 0.2, 0.3);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawCubWithMaterial(6);
	glBlendFunc(GL_ONE, GL_ZERO);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
	glPopMatrix();

	glPopMatrix();
}

void drawWall() {
	glPushMatrix();
	glTranslatef(-7 * tam, 4 * tam, 0);
	malha3(0,17);
	glScalef(1, 4, 0.5);
	drawCubWithTexture3(1, 4, 0.5, 17, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(7 * tam, 4 * tam, 0);
	malha3(0,17);
	glScalef(1, 4, 0.5);
	drawCubWithTexture3(1, 4, 0.5, 17, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 8.5 * tam, 0);
	glScalef(8, 0.5, 0.5);
	drawCubWithTexture(8, 0.5, 0.5, 17, 0);
	glPopMatrix();
}

void dwawbutton(GLfloat  trans) {
	glPushMatrix();
	glTranslatef((6 + 0.5 + 0.5) * tam, 2.75 * tam, (0.05 + 0.5) * tam);
	glPushMatrix();
	glTranslatef(0, 0 * tam, (0.05 + 0.05 - trans) * tam);
	glScalef(0.15, 0.15, 0.05);
	drawCubWithMaterial(17);
	glPopMatrix();
	glScalef(0.5, 0.5, 0.05);
	drawCubWithMaterial(17);
	glPopMatrix();
}

void drawDoor() {
	malha(1,7);
	glPushMatrix();
	glTranslatef(-4.75 * tam, 2.75 * tam, 0);
	glScalef(1.25, 2.75, 0.25);
	drawCubWithMaterial2(7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.75 * tam, 2.75 * tam, 0);
	glScalef(3.25, 2.75, 0.25);
	drawCubWithMaterial2(7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6.75 * tam, 0);
	glScalef(6, 1.25, 0.25);
	drawCubWithMaterial2(7);
	glPopMatrix();

}

void drawDoor2(GLfloat  angulo, GLfloat angulo_2) {

	glPushMatrix();
	glTranslatef(-2 * tam, 2.75 * tam, 0);
	glTranslatef(-1.5 * tam, 0, 0);
	glRotatef(angulo, 0, 1, 0);
	glTranslatef(1.5 * tam, 0, 0);
	/*
	glPushMatrix();
	glScalef(1.5, 2.75, 0.15);
	drawCub();
	glPopMatrix();
	*/

	glPushMatrix();
	glTranslatef(0, (2.75 - 0.4) * tam, 0);
	glScalef(1.5, 0.4, 0.15);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (-2.75 + 0.4) * tam, 0);
	glScalef(1.5, 0.4, 0.15);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((-1.5 + 0.3) * tam, 0, 0);
	glScalef(0.3, (2.75 - 0.8), 0.15);
	drawCubWithMaterial(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((1.5 - 0.8) * tam, 0, 0);
	glScalef(0.8, (2.75 - 0.8), 0.15);
	drawCubWithMaterial(2);
	glPopMatrix();


	//maçaneta
	glPushMatrix();
	glTranslatef(0.8 * tam, 0, (0.06 + 0.15) * tam);
	glTranslatef(0.3 * tam, 0, 0);
	glRotatef(angulo_2, 0, 0, 1);
	glTranslatef(-0.3 * tam, 0, 0);
	glPushMatrix();
	glScalef(0.35, 0.06, 0.06);
	drawCubWithMaterial(11);
	glPopMatrix();

	glTranslatef(0, 0, -2 * (0.06 + 0.15) * tam);
	glScalef(0.35, 0.06, 0.06);
	drawCubWithMaterial(11);
	glPopMatrix();

	glPushMatrix();
	glTranslatef((0.07 - (0.14 * angulo_2 / 30) + 1.5) * tam, -0.2, 0);
	glScalef(0.07, 0.09, 0.04);
	drawCubWithMaterial(11);
	glPopMatrix();

	glPopMatrix();
}

void drawScene() {
	/*
	if (AumentaLuzDir) {
		CorAmbDir[0] = (CorAmbDir[0] + 0.1);
		CorDifDir[0] = (CorDifDir[0] + 0.1);
		CorEspDir[0] = (CorEspDir[0] + 0.1);
		CorAmbDir[1] = (CorAmbDir[1] + 0.1);
		CorDifDir[1] = (CorDifDir[1] + 0.1);
		CorEspDir[1] = (CorEspDir[1] + 0.1);
		CorAmbDir[2] = (CorAmbDir[2] + 0.1);
		CorDifDir[2] = (CorDifDir[2] + 0.1);
		CorEspDir[2] = (CorEspDir[2] + 0.1);
		printf("a");
		if (CorAmbDir[0] > 1) {
			CorAmbDir[0] = 1;
		}
		if (CorAmbDir[1] > 1) {
			CorAmbDir[1] = 1;
		}
		if (CorAmbDir[2] > 1) {
			CorAmbDir[2] = 1;
		}
		if (CorDifDir[0] > 1) {
			CorDifDir[0] = 1;
		}
		if (CorDifDir[1] > 1) {
			CorDifDir[1] = 1;
		}
		if (CorDifDir[2] > 1) {
			CorDifDir[2] = 1;
		}
		if (CorAmbPont[0] > 1) {
			CorAmbDir[0] = 1;
		}
		if (CorAmbPont[1] > 1) {
			CorAmbDir[1] = 1;
		}
		if (CorAmbPont[2] > 1) {
			CorAmbDir[2] = 1;
		}
	}
	if (DiminuiLuzDir) {
		CorAmbDir[0] = (CorAmbDir[0] - 0.1);
		CorDifDir[0] = (CorDifDir[0] - 0.1);
		CorEspDir[0] = (CorEspDir[0] - 0.1);
		CorAmbDir[1] = (CorAmbDir[1] - 0.1);
		CorDifDir[1] = (CorDifDir[1] - 0.1);
		CorEspDir[1] = (CorEspDir[1] - 0.1);
		CorAmbDir[2] = (CorAmbDir[2] - 0.1);
		CorDifDir[2] = (CorDifDir[2] - 0.1);
		CorEspDir[2] = (CorEspDir[2] - 0.1);
		printf("a");
		if (CorAmbDir[0] < 0) {
			CorAmbDir[0] = 0;
		}
		if (CorAmbDir[1] < 0) {
			CorAmbDir[1] = 0;
		}
		if (CorAmbDir[2] < 0) {
			CorAmbDir[2] = 0;
		}
		if (CorDifDir[0] < 0) {
			CorDifDir[0] = 0;
		}
		if (CorDifDir[1] < 0) {
			CorDifDir[1] = 0;
		}
		if (CorDifDir[2] < 0) {
			CorDifDir[2] = 0;
		}
		if (CorAmbDir[0] < 0) {
			CorAmbDir[0] = 0;
		}
		if (CorAmbDir[1] < 0) {
			CorAmbDir[1] = 0;
		}
		if (CorAmbDir[2] < 0) {
			CorAmbDir[2] = 0;
		}

	}
	*/
	/*
	if (!look) {
		if (UP)   aVisao2 = (aVisao2 + 0.08);
		if (DOWN) aVisao2 = (aVisao2 - 0.08);
		if (LEFT)  aVisao = (aVisao + 0.08);
		if (RIGHT) aVisao = (aVisao - 0.08);
		if (aVisao2 > PI / 2) aVisao2 = PI / 2;
		else {
			if (aVisao2 < -PI / 2) aVisao2 = -PI / 2;
		}
		obsP[1] = rVisao * sin(aVisao2) + 2 * tam;

		obsP[0] = rVisao * cos(aVisao2) * cos(aVisao);
		obsP[2] = rVisao * cos(aVisao2) * sin(aVisao);

		obsL[1] = rVisaoL * sin(aVisao2L) + 2 * tam + obsP[1];
		obsL[0] = rVisaoL * cos(aVisao2L) * cos(aVisaoL) + obsP[0];
		obsL[2] = rVisaoL * cos(aVisao2L) * sin(aVisaoL) + obsP[2];
	}
	*/

if (descer) {
	obsP[1] -= 0.08;
	if (obsP[1] < 1) obsP[1] = 1;
}

	float hip = sqrt(obsP[2] * obsP[2] + obsP[0] * obsP[0]);
	if (!look) {
		if (Door1_up) { obsP[2] += sin(aVisaoL) * 0.08; obsP[0] += cos(aVisaoL) * 0.08; }
		if (Door1_down) { obsP[2] -= sin(aVisaoL) * 0.08; obsP[0] -= cos(aVisaoL) * 0.08; }
		if (Door2_open) { obsP[2] += sin(aVisaoL - PI / 2) * 0.08; obsP[0] += cos(aVisaoL - PI / 2) * 0.08; }
		if (Door2_close) { obsP[2] -= sin(aVisaoL - PI / 2) * 0.08; obsP[0] -= cos(aVisaoL - PI / 2) * 0.08; }
		hip = sqrt(obsP[2] * obsP[2] + obsP[0] * obsP[0]);
		float tn = sqrt(hip * hip + obsP[1] * obsP[1]);
		if (hip > (15-1)* cos(acos(hip / tn))) {
			obsP[2] = sin(asin(obsP[2] / hip)) * (15-1)*cos(acos(hip/tn));
			obsP[0] = cos(acos(obsP[0]/hip)) * (15-1)*cos(acos(hip/tn));
		}


		obsL[1] = rVisaoL * sin(aVisao2L) + 2 * tam + obsP[1];
		obsL[0] = rVisaoL * cos(aVisao2L) * cos(aVisaoL) + obsP[0];
		obsL[2] = rVisaoL * cos(aVisao2L) * sin(aVisaoL) + obsP[2];
	}
	if (subir) {
		obsP[1] += 0.08;
		if (sqrt(hip * hip + obsP[1] * obsP[1]) > (15 - 1)) {
			obsP[1] = sin(atan(obsP[1] / hip)) * (15 - 1);
		}
	}
	

		if (UP)   aVisao2L = (aVisao2L + 0.08);
		if (DOWN) aVisao2L = (aVisao2L - 0.08);
		if (LEFT)  aVisaoL = (aVisaoL - 0.08);
		if (RIGHT) aVisaoL = (aVisaoL + 0.08);
		if (aVisao2L > PI / 2) aVisao2L = PI / 2;
		else {
			if (aVisao2L < -PI / 2) aVisao2L = -PI / 2;
		}
		obsL[1] = rVisaoL * sin(aVisao2L) + 2 * tam + obsP[1];
		obsL[0] = rVisaoL * cos(aVisao2L) * cos(aVisaoL) + obsP[0];
		obsL[2] = rVisaoL * cos(aVisao2L) * sin(aVisaoL) + obsP[2];
	
	


	if (frenteVisivel == 0)
		glCullFace(GL_FRONT);
	if (frenteVisivel == 1)
		glCullFace(GL_BACK);
	if (frenteVisivel == 2)
		glCullFace(GL_FRONT_AND_BACK);

	if (look) {
		if (Door1_up) {
			if (angulo1 < 90)
				angulo1 += 1.5;
			else {
				if (trans > -8) {
					if (aux > -0.25) {
						aux -= 0.025;
						if (aux < -0.25) {
							aux = -0.25;
						}
					}
					else {
						trans -= 0.25;
					}
				}
			}
			if (t_button < 0.07) {
				t_button += 0.0125;
			}
		}
		else {
			if (t_button > 0 && !Door1_down) {
				t_button -= 0.0125;
			}
		}

		if (Door1_down) {
			if (trans < 0)
				trans += 0.25;
			else {
				if (angulo1 > 0) {
					if (aux < 0) {
						aux += 0.025;
						if (aux > 0) {
							aux = 0;
						}
					}
					else {
						angulo1 -= 1.5;
					}
				}
			}
			if (t_button < 0.07) {
				t_button += 0.0125;
			}
		}
		else {
			if (t_button > 0 && !Door1_up) {
				t_button -= 0.0125;
			}
		}

		if (open) {
			if (angulo3 < 30) {
				angulo3 += 5;
			}
		}

		if (Door2_open) {
			if (angulo3 == 30 || angulo2 > 0) {
				if (angulo2 < 90)
					angulo2 += 3;
			}
			else {
				if (!open) {
					angulo3 += 10;
				}
			}
		}

		if (!open) {
			if (angulo3 > 0)
				angulo3 -= 5;
		}

		if (Door2_close) {
			if (angulo2 > 0)
				angulo2 -= 3;
		}
	}
	glBlendFunc(GL_ONE, GL_ZERO);
	drawWall();
	dwawbutton(t_button);
	glPushMatrix();
	glTranslatef(0, (8 + aux) * tam, trans * tam);
	glRotatef(-angulo1, 1, 0, 0);
	glTranslatef(0, -8 * tam, 0);
	drawDoor();
	drawDoor2(angulo2, angulo3);
	glPopMatrix();

	if (obsP[0] / hip < 1 && obsP[0] / hip >0) {
		drawCandeeiro(-1); drawCandeeiro(1);
	}
	else {
		drawCandeeiro(1); drawCandeeiro(-1);
	}

	glTranslatef(0, (8 + aux) * tam, trans * tam);
	glRotatef(-angulo1, 1, 0, 0);
	glTranslatef(0, -8 * tam, 0);
	glTranslatef(-2 * tam, 2.75 * tam, 0);
	glTranslatef(-1.5 * tam, 0, 0);
	glRotatef(angulo2, 0, 1, 0);
	glTranslatef(1.5 * tam, 0, 0);
	glTranslatef((-1.5 + (1.5 - 0.3 - 0.8) + 0.6)* tam, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	malha2(5);
	glBlendFunc(GL_ONE, GL_ZERO);


}

void iluminacao() {
	if (LuzDir) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, PosicaoDir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, CorAmbDir);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, CorDifDir);
	glLightfv(GL_LIGHT0, GL_SPECULAR, CorEspDir);

	/*
	glLightfv(GL_LIGHT1, GL_POSITION, PosicaoPont1);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, CorAmbPont);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, CorDifPont);
	glLightfv(GL_LIGHT1, GL_SPECULAR, CorEspPont);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05);
	*/
	//glEnable(GL_LIGHT1);
	/*
	float pos[] = { obsP[0], obsP[1], obsP[2], 1 };
	float dir[] = { obsL[0] - obsP[0], obsL[1] - obsP[1], obsL[2] - obsP[2], 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, CorDifPont);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
	*/

	glLightfv(GL_LIGHT2, GL_POSITION, PosicaoPont1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, CorAmbPont);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, CorDifPont);
	glLightfv(GL_LIGHT2, GL_SPECULAR, CorEspPont);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05);


	glLightfv(GL_LIGHT3, GL_POSITION, PosicaoPont2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, CorAmbPont);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, CorDifPont);
	glLightfv(GL_LIGHT3, GL_SPECULAR, CorEspPont);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.05);
	
}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(obsP[0], obsP[1], obsP[2], obsL[0], obsL[1], obsL[2], 0, 1, 0);

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	iluminacao();
	drawchao();
	drawBola();
	drawScene();

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'r':
	case 'R':
		frenteVisivel = (frenteVisivel + 1) % 3;
		break;

	case 'W':
	case 'w':
		Door1_up = true;
		break;

	case 'S':
	case 's':
		Door1_down = true;
		break;

	case 'a':
	case 'A':
		Door2_open = true;
		break;

	case 'd':
	case 'D':
		Door2_close = true;
		break;
	case 'e':
	case 'E':
		open = true;
		break;

	case 'x':
	case 'X':
		subir = true;
		break;

	case 'z':
	case 'Z':
		descer = true;
		break;
	case 'g':
	case 'G':
		AumentaLuzDir = true;
		break;
	case 'f':
	case 'F':
		DiminuiLuzDir = true;
		break;
	case 'c':
	case 'C':
		look = true;
		break;
	case 27:
		exit(0);
		break;
	}

}

void keyboard2(unsigned char key, int x, int y) {


	switch (key) {

	case 'W':
	case 'w':
		Door1_up = false;
		break;

	case 'S':
	case 's':
		Door1_down = false;
		break;

	case 'a':
	case 'A':
		Door2_open = false;
		break;

	case 'd':
	case 'D':
		Door2_close = false;
		break;

	case 'e':
	case 'E':
		open = false;
		break;

	case 'x':
	case 'X':
		subir = false;
		break;

	case 'z':
	case 'Z':
		descer = false;
		break;
	case '1':
		CorDifPont[0] = ((int)CorDifPont[0] + 1) % 2;
		CorEspPont[0] = ((int)CorEspPont[0] + 1) % 2;
		break;
	case '2':
		CorDifPont[1] = ((int)CorDifPont[1] + 1) % 2;
		CorEspPont[1] = ((int)CorEspPont[1] + 1) % 2;
		break;
	case '3':
		CorDifPont[2] = ((int)CorDifPont[2] + 1) % 2;
		CorEspPont[2] = ((int)CorEspPont[2] + 1) % 2;
		break;
	case 'g':
	case 'G':
		AumentaLuzDir = false;
		break;
	case 'f':
	case 'F':
		DiminuiLuzDir = false;
		break;
	case 'q':
	case 'Q':
		LuzDir = (LuzDir+1)%2;
		break;
	case 'c':
	case 'C':
		look = false;
		break;
	case '+':
		wmCoef += 10;
		if (wmCoef > 128) wmCoef = 128;
		printf("%d\n", wmCoef);
		break;
	case '-':
		wmCoef -= 10;
		if (wmCoef < 10) wmCoef = 10;
		printf("%d\n", wmCoef);
		break;
	case 'M':
		localAttCon++;
		if (localAttCon > 30) localAttCon = 10;
		break;
	case 'm':
		localAttCon--;
		if (localAttCon < 1) localAttCon = 1;
		break;
	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y) {
	if (key == GLUT_KEY_UP)   UP = true;
	if (key == GLUT_KEY_DOWN) DOWN = true;
	if (key == GLUT_KEY_LEFT)  LEFT = true;
	if (key == GLUT_KEY_RIGHT) RIGHT = true;
}

void teclasNotAscii2(int key, int x, int y) {
	if (key == GLUT_KEY_UP)   UP = false;
	if (key == GLUT_KEY_DOWN) DOWN = false;
	if (key == GLUT_KEY_LEFT) LEFT = false;
	if (key == GLUT_KEY_RIGHT) RIGHT = false;

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("|Observador:'SETAS'|        |Porta da garagem:'w/s'|        |Porta normal:'a/d'|        |Destrancar:'e'|        |Zoom:'z/x'|");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutSpecialUpFunc(teclasNotAscii2);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard2);
	glutTimerFunc(20, Timer, 1);

	glutMainLoop();

	return 0;
}


