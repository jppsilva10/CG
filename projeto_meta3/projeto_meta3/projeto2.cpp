/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2019/20
	................................................... JHenriques / EPolisciuc
	======================================================================================= */


	//.................................................... Bibliotecas necessarias
#include <windows.h>			// printf
#include <stdio.h>				// printf
#include <fstream>				// printf

#include <string>
#include <fstream>

#include <errno.h>
#include <GL\glew.h>			// openGL
//#include <GL\freeGlut.h>		// openGL
#include <GL/freeglut.h>
#include "RgbImage.h"

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

//.................................................... Variaveis
GLint	wScreen = 900, hScreen = 750;		//.. janela

//------------------------------------------------------------ Observador 

GLint  uniOp;
GLint  uniDir;
GLint  uniCa;
GLint transfrom;
GLint translate;
GLint reflection;
GLint refraction;
GLint Luz;
GLint Time;
GLint Animation;
float  r = 0;
float  t = 0;
float  l = 0;
float time = 0;
float animation = 0;
float transformatioMatrix[4][4] = { {1, 0, 0, 0},
									{0, 1, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1} };

float  Direcao[] = { 1, 0, 0 };
float  opcao = -45;
//float  Camera[] = { 0, 1, -3 };
float rotacao1 = 0;
float rotacao2 = 0;

bool UP = false;
bool DOWN = false;
bool LEFT = false;
bool RIGHT = false;

GLfloat  rVisao = 6, aVisao = -0.5 * 3.14, aVisao2 = 0, incVisao = 0.05;

GLfloat  Camera[] = { rVisao * cos(aVisao2) * cos(aVisao), rVisao * sin(aVisao2), rVisao * cos(aVisao2) * sin(aVisao) };

GLfloat  angZoom = 90;
GLfloat  incZoom = 3;

//------------------------------------------ Definição dos ficheiros dos shaders: vertices + fragmentos
char filenameV[] = "Vshader.txt";
char filenameF[] = "Fshader.txt";

//---------------------------------------------------------- SHADERS variaveis
char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram;



GLuint   text[8];
int      textLoc, text7Loc;
RgbImage imag;
GLint  uni_op;
float op;





GLuint depthMapFBO[1];


void initTexturas()
{
	//----------------------------------------- Chao

	glGenTextures(1, &text[7]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, text[7]);
	imag.LoadBmpFile("right.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("left.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("top.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("bottom.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("back.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("front.bmp");
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
}

//============================================= 1. Ler um ficheiro com um shader
char* readShaderFile(char* FileName) {

	char* DATA = NULL;
	int   flength = 0;
	FILE* filepoint;
	errno_t err;

	err = fopen_s(&filepoint, FileName, "r");
	if (!err) {
		fseek(filepoint, 0, SEEK_END);
		flength = ftell(filepoint);
		rewind(filepoint);

		DATA = (char*)malloc(sizeof(char) * (flength + 1));
		flength = fread(DATA, sizeof(char), flength, filepoint);

		DATA[flength] = '\0';
		fclose(filepoint);
		return DATA;
	}
	else {
		printf(" --------  Error while reading  %s ", FileName);
	}
}


//============================================= 2. Criar, compilar, linkar, e usar
void BuiltShader(void) {

	GLEW_ARB_vertex_shader;
	GLEW_ARB_fragment_shader;

	//......................................................... Criar
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(filenameV);
	FragmentShaderSource = readShaderFile(filenameF);

	const char* VS = VertexShaderSource;
	const char* FS = FragmentShaderSource;
	glShaderSource(VertexShader, 1, &VS, NULL);
	glShaderSource(FragmentShader, 1, &FS, NULL);
	free(VertexShaderSource);
	free(FragmentShaderSource);

	//......................................................... Compilar
	glCompileShaderARB(VertexShader);
	glCompileShaderARB(FragmentShader);

	//......................................................... Criar e Linkar
	ShaderProgram = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	//......................................................... Usar
	glUseProgramObjectARB(ShaderProgram);
}


void InitShader(void) {

	//------------------------ Criar+linkar
	BuiltShader();

	//------------------------------------  UYNIORM

	uniDir = glGetUniformLocation(ShaderProgram, "Direcao");
	glUniform3fv(uniDir, 1, Direcao);
	uniOp = glGetUniformLocation(ShaderProgram, "opcao");
	glUniform1f(uniOp, opcao);
	textLoc = glGetUniformLocation(ShaderProgram, "text");
	text7Loc = glGetUniformLocation(ShaderProgram, "text7");

	uni_op = glGetUniformLocation(ShaderProgram, "op");
	glUniform1f(uni_op, op);

	uniCa = glGetUniformLocation(ShaderProgram, "cameraPosition");
	glUniform3fv(uniCa, 1, Camera);

	transfrom = glGetUniformLocation(ShaderProgram, "transfom");

	translate = glGetUniformLocation(ShaderProgram, "translate");

	reflection = glGetUniformLocation(ShaderProgram, "reflection");
	refraction = glGetUniformLocation(ShaderProgram, "refraction");
	Luz = glGetUniformLocation(ShaderProgram, "Luz");

	Time = glGetUniformLocation(ShaderProgram, "Time");
	Animation = glGetUniformLocation(ShaderProgram, "Animation");
}


//============================================= 3.Libertar os Shaders
void DeInitShader(void) {
	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(ShaderProgram);
}


//=========================================================================== 
//==================================================================  SHADERS
//=========================================================================== 



//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------

void Inicializa(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor com base na cor dos vertices
	glEnable(GL_DEPTH_TEST);
	initTexturas();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------
void cubo(float tam) {
	glPushMatrix();
	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(-tam, tam, -tam);
	glVertex3d(-tam, -tam, -tam);
	glVertex3d(-tam, -tam, tam);
	glVertex3d(-tam, tam, tam);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(-0, 0, 1);
	glVertex3d(-tam, tam, tam);
	glVertex3d(-tam, -tam, tam);
	glVertex3d(tam, -tam, tam);
	glVertex3d(tam, tam, tam);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3d(-tam, tam, tam);
	glVertex3d(-tam, tam, -tam);
	glVertex3d(tam, tam, -tam);
	glVertex3d(tam, tam, tam);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3d(tam, tam, tam);
	glVertex3d(tam, -tam, tam);
	glVertex3d(tam, -tam, -tam);
	glVertex3d(tam, tam, -tam);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3d(tam, tam, -tam);
	glVertex3d(tam, -tam, -tam);
	glVertex3d(-tam, -tam, -tam);
	glVertex3d(-tam, tam, -tam);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3d(-tam, -tam, tam);
	glVertex3d(-tam, -tam, -tam);
	glVertex3d(tam, -tam, -tam);
	glVertex3d(tam, -tam, tam);
	glEnd();
	glPopMatrix();
}

void skybox() {
	//glActiveTexture(GL_TEXTURE1); // Texture unit 0
	//glEnable(GL_TEXTURE_2D);
	//glNormal3f(0, 0, 1);
	///glBindTexture(GL_TEXTURE_2D, text[1]);
	///glUniform1i(textLoc, 0);
	glBegin(GL_QUADS);
			glTexCoord2f(0.014, 1.0);
			glVertex3d(-8, 8, -8);

			glTexCoord2f(0.014, 0.0);
			glVertex3d(-8, -8, -8);

			glTexCoord2f(1.0, 0.0);
			glVertex3d(8, -8, -8);

			glTexCoord2f(1.0, 1.0);
			glVertex3d(8, 8, -8);

	glEnd();

	//glNormal3f(0, 0, -1);
	//glBindTexture(GL_TEXTURE_2D, text[2]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.014, 1.0);
	glVertex3d(8, 8, 8);

	glTexCoord2f(0.014, 0.0);
	glVertex3d(8, -8, 8);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(-8, -8, 8);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(-8, 8, 8);

	glEnd();

	//glNormal3f(1, 0, 0);
	//glBindTexture(GL_TEXTURE_2D, text[3]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.014, 1.0);
	glVertex3d(-8, 8, 8);

	glTexCoord2f(0.014, 0.0);
	glVertex3d(-8, -8, 8);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(-8, -8, -8);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(-8, 8, -8);

	glEnd();

	//glNormal3f(-1, 0, 0);
	//glBindTexture(GL_TEXTURE_2D, text[4]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.014, 1.0);
	glVertex3d(8, 8, -8);

	glTexCoord2f(0.014, 0.0);
	glVertex3d(8, -8, -8);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(8, -8, 8);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(8, 8, 8);

	glEnd();

	//glNormal3f(0, -1, 0);
	//glBindTexture(GL_TEXTURE_2D, text[5]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.014, 1.0);
	glVertex3d(-8, 8, 8);

	glTexCoord2f(0.014, 0.0);
	glVertex3d(-8, 8, -8);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(8, 8, -8);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(8, 8, 8);

	glEnd();

	//glNormal3f(0, 1, 0);
	//glBindTexture(GL_TEXTURE_2D, text[6]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.014, 1.0);
	glVertex3d(-8, -8, -8);

	glTexCoord2f(0.014, 0.0);
	glVertex3d(-8, -8, 8);

	glTexCoord2f(1.0, 0.0);
	glVertex3d(8, -8, 8);

	glTexCoord2f(1.0, 1.0);
	glVertex3d(8, -8, -8);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

GLUquadricObj* bola = gluNewQuadric();
void Bola()
{
	glPushMatrix();
	gluQuadricDrawStyle(bola, GLU_FILL);
	gluQuadricNormals(bola, GLU_SMOOTH);
	gluQuadricTexture(bola, GL_TRUE);
	gluSphere(bola, 0.3, 100, 100);
	glPopMatrix();
}

//---------------------------------------- Função callback de desenho (principal)
void Desenha(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Camera[0], Camera[1], Camera[2], 0, 0, 0, 0, 1, 0);



	if (UP)   aVisao2 = (aVisao2 + 0.08);
	if (DOWN) aVisao2 = (aVisao2 - 0.08);
	if (LEFT)  aVisao = (aVisao + 0.08);
	if (RIGHT) aVisao = (aVisao - 0.08);
	if (aVisao2 > 3.14 / 2) aVisao2 = 3.14 / 2;
	else {
		if (aVisao2 < -3.14 / 2) aVisao2 = -3.14 / 2;
	}
	Camera[1] = rVisao * sin(aVisao2);

	Camera[0] = rVisao * cos(aVisao2) * cos(aVisao);
	Camera[2] = rVisao * cos(aVisao2) * sin(aVisao);

	glUniform3fv(uniCa, 1, Camera);





	glEnable(GL_TEXTURE_2D);

	glUseProgramObjectARB(ShaderProgram);

	glUniform1f(uniOp, opcao);
	glUniform3fv(uniDir, 1, Direcao);

	Direcao[0] = 2*cos(3.14 * opcao / 180.0) * cos(3.14 * 45 / 180.0);
	Direcao[1] = 2*sin(3.14 * 60 / 180.0);
	Direcao[2] = 2*sin(3.14 * opcao / 180.0) * cos(3.14 * 45 / 180.0);

	op = 1;
	glUniform1f(uni_op, op);
	glUniform1f(translate, 0);

	//----
	glActiveTexture(GL_TEXTURE0); // Texture unit 0
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, text[7]);
	glUniform1i(text7Loc, 0);
	//---

	skybox();
	
	op = 0;
	glUniform1f(uni_op, op);
	glUniform1f(translate, 0);

	//----
	glActiveTexture(GL_TEXTURE0); // Texture unit 0
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, text[7]);
	glUniform1i(text7Loc, 0);
	//---

	//glutSolidTeapot(1);
	//cubo(0.3);
	Bola();
	
	op = 2;
	glUniform1f(uni_op, op);
	glUniform1f(translate, -2);

	glPushMatrix();
	glutSolidTeapot(1);
	//cubo(1);
	glPopMatrix();

	op = 3;
	glUniform1f(uni_op, op);
	glUniform1f(translate, 2);

	glPushMatrix();
	glutSolidTeapot(1);
	glPopMatrix();



	glutSwapBuffers();						//.. actualiza ecran
	
}


// -----------------------------------------------------------------------

//¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨Função callback eventos teclado 
void Teclado(unsigned char key, int x, int y) {

	switch (key) {

	case 'o':
	case 'O':
		opcao = opcao + 10;
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		r = ((int)r + 1) % 2;
		glUniform1f(reflection, r);
		glutPostRedisplay();
		break;
	case 't':
	case 'T':
		t = ((int)t + 1) % 2;
		glUniform1f(refraction, t);
		glutPostRedisplay();
		break;

	case 'l':
	case 'L':
		l = ((int)t + 1) % 2;
		glUniform1f(Luz, l);
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		animation = ((int)animation + 1) % 2;
		glUniform1f(Animation, animation);
		time = 0;
		glUniform1f(Time, time);
		glutPostRedisplay();
		break;

	case 27:					//ESC
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
	time = ((int)time + 1) % 120;
	glUniform1f(Time, time);
}

//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 750);					//		:dimensoes (pixeis)
	glutInitWindowPosition(500, 40);				//		:localizacao
	glutCreateWindow("| O: posição da luz | L: tipo de luz | R: reflexão | T: Refração | A: Animação |");

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Inicializa();

	//------------------------------------  GLEW
	GLenum err = glewInit();
	InitShader();

	DeInitShader();



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	glutSpecialFunc(teclasNotAscii);
	glutSpecialUpFunc(teclasNotAscii2);
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Teclado);
	glutTimerFunc(20, Timer, 1);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutMainLoop();								//===4:Inicia processamento
	return 1;
}
