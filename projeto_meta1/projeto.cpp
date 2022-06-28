

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

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
static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//…………………………………………………… Direita
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
	//……………………………………………………… (Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 
		//……………………………………………………… (baixo
		-tam,  -tam,  tam,	// 12 
		-tam,  -tam, -tam,	// 13
		 tam,  -tam, -tam,	// 14 
		 tam,  -tam,  tam,	// 15 
		//……………………………………………………… (frente
		-tam,   tam,  tam,	// 16 
		-tam,  -tam,  tam,	// 17
		 tam,  -tam,  tam,	// 18 
		 tam,   tam,  tam,	// 19 
		//……………………………………………………… (traz
		 tam,   tam, -tam,	// 20 
		 tam,  -tam, -tam,	// 21
		-tam,  -tam, -tam,	// 22 
		-tam,   tam, -tam,	// 23 
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
// nao está feito !!


//=========================================================== FACES DA MESA
GLboolean   frenteVisivel = 1;
static GLuint     cima[] = { 8, 11, 10,  9 };   // regra da mao direita
//?? falta a esquerda 
static GLuint     esquerda[] = { 0, 1, 2,  3 };
//?? falta a direita 
static GLuint     direita[] = { 4, 7, 6,  5 };
static GLuint     baixo[] = { 12, 13, 14,  15 };
static GLuint     frente[] = { 16, 17, 18,  19 };
static GLuint     traz[] = { 20, 21, 22, 23 };

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 1200, hScreen = 900;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, aVisao2=0, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao2) * cos(aVisao), rVisao * sin(aVisao2) + 2 * tam, rVisao * cos(aVisao2) * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;

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

bool aproximar = false;
bool afastar = false;

bool UP = false;
bool DOWN = false;
bool LEFT = false;
bool RIGHT = false;

//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);

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

void drawCub() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, traz);
}

void drawWall() {
	glPushMatrix();
	glTranslatef(-7 * tam, 4 * tam, 0);
	glScalef(1, 4, 0.5);
	drawCub();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7 * tam, 4 * tam, 0);
	glScalef(1, 4, 0.5);
	drawCub();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 8.5 * tam, 0);
	glScalef(8, 0.5, 0.5);
	drawCub();
	glPopMatrix();
}

void dwawbutton(GLfloat  trans) {
	glPushMatrix();
	glTranslatef((6+0.5+0.5) * tam, 2.75 * tam, (0.05+0.5)*tam);
	glPushMatrix();
	glTranslatef(0, 0 * tam, (0.05+0.05-trans) * tam);
	glScalef(0.15, 0.15, 0.05);
	drawCub();
	glPopMatrix();
	glScalef(0.5, 0.5, 0.05);
	drawCub();
	glPopMatrix();
}

void drawDoor() {
	glPushMatrix();
	glTranslatef(-4.75*tam, 2.75 * tam, 0);
	glScalef(1.25, 2.75, 0.25);
	drawCub();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.75 * tam, 2.75 * tam, 0);
	glScalef(3.25, 2.75, 0.25);
	drawCub();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6.75 * tam, 0);
	glScalef(6, 1.25, 0.25);
	drawCub();
	glPopMatrix();
	
}

void drawDoor2(GLfloat  angulo, GLfloat angulo_2) {
	glPushMatrix();
	glTranslatef(-2 * tam, 2.75 * tam, 0);
	glTranslatef(-1.5 * tam, 0, 0);
	glRotatef(angulo, 0, 1, 0);
	glTranslatef(1.5 * tam,0, 0);
	/*
	glPushMatrix();
	glScalef(1.5, 2.75, 0.15);
	drawCub();
	glPopMatrix();
	*/
	
	glPushMatrix();
	glTranslatef(0, (2.75-0.4)*tam, 0);
	glScalef(1.5, 0.4, 0.15);
	drawCub();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, (-2.75+0.4)*tam, 0);
	glScalef(1.5, 0.4, 0.15);
	drawCub();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef((-1.5+0.3)*tam, 0, 0);
	glScalef(0.3, (2.75-0.8), 0.15);
	drawCub();
	glPopMatrix();

	glPushMatrix();
	glTranslatef((1.5-0.8)*tam, 0, 0);
	glScalef(0.8, (2.75-0.8), 0.15);
	drawCub();
	glPopMatrix();
	
	
	//maçaneta
	glPushMatrix();
	glTranslatef(0.8*tam, 0, (0.06+0.15)*tam);
	glTranslatef(0.3 * tam, 0, 0);
	glRotatef(angulo_2, 0, 0, 1);
	glTranslatef(-0.3 * tam, 0, 0);
	glPushMatrix();
	glScalef(0.35, 0.06, 0.06);
	drawCub();
	glPopMatrix();

	glTranslatef(0, 0, -2*(0.06 + 0.15) * tam);
	glScalef(0.35, 0.06, 0.06);
	drawCub();
	glPopMatrix();

	glTranslatef((0.07 - (0.14*angulo_2/30) +1.5)*tam, -0.2, 0);
	glScalef(0.07, 0.09, 0.04);
	drawCub();

	glPopMatrix();
}

void drawScene() {

	if (UP)   aVisao2 = (aVisao2 + 0.08);
	if (DOWN) aVisao2 = (aVisao2 - 0.08);
	if (LEFT)  aVisao = (aVisao + 0.08);
	if (RIGHT) aVisao = (aVisao - 0.08);
	if (aVisao2 > PI/2) aVisao2 = PI/2;
	else { 
		if (aVisao2 < -PI/2) aVisao2 = -PI/2;
	}
	obsP[1] = rVisao * sin(aVisao2) + 2 * tam;

	obsP[0] = rVisao * cos(aVisao2) * cos(aVisao);
	obsP[2] = rVisao * cos(aVisao2) * sin(aVisao);


	if (frenteVisivel == 0)
		glCullFace(GL_FRONT);
	if (frenteVisivel == 1)
		glCullFace(GL_BACK);
	if (frenteVisivel == 2)
		glCullFace(GL_FRONT_AND_BACK);

	if (aproximar) {
		if (angZoom > 45)
			angZoom -= 0.5;
	}
	if (afastar) {
		if (angZoom < 120)
			angZoom += 0.5;
	}

	if (Door1_up) {
		if (angulo1 < 90)
			angulo1+=1.5;
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
			trans+=0.25;
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

	if(!open) {
		if (angulo3 > 0)
			angulo3 -= 5;
	}

	if (Door2_close) {
		if (angulo2 > 0)
			angulo2 -= 3;
	}

	drawWall();
	dwawbutton(t_button);
	glPushMatrix();
	glTranslatef(0, (8+aux) * tam, trans*tam);
	glRotatef(-angulo1, 1, 0, 0);
	glTranslatef(0, -8 * tam, 0);
	drawDoor();
	drawDoor2(angulo2, angulo3);
	glPopMatrix();


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
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 2*tam, 0, 0, 1, 0);


	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawScene();

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'f':
	case 'F':
		frenteVisivel = (frenteVisivel + 1) % 3;
		break;

	case 'W':
	case 'w':
		Door1_up=true;
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
		aproximar = true;
		break;

	case 'z':
	case 'Z':
		afastar = true;
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
		aproximar = false;
		break;

	case 'z':
	case 'Z':
		afastar = false;
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


