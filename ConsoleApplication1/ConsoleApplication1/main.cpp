#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Constants.h"
#include "Vector2.h"
#include "Polygon.h"
#include "FenetreRemplissageInterface.h"

void reshape(int w, int l)
{
	glViewport(0, 0, w, l);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > l)
		glOrtho((float)-w / l, (float)w / l,
		-1.0, 1.0,
		-1.0, 1.0);
	else
		glOrtho(-1.0, 1.0,
		(float)-l / w, (float)l / w,
		-1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Dessin de la palette couleur 
	//Rouge
	glBegin(GL_POLYGON);
	glColor3f(0.01f, 0.0f, 0.0f);
	glVertex2f(0.7, -0.7);
	glVertex2f(0.8, -0.7);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.8, -1.0);
	glVertex2f(0.7, -1.0);
	glEnd();

	//Bleu
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.01f, 0.0f);
	glVertex2f(0.8, -0.7);
	glVertex2f(0.9, -0.7);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.9, -1.0);
	glVertex2f(0.8, -1.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.01f);
	glVertex2f(0.9, -0.7);
	glVertex2f(1.0, -0.7);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0, -1.0);
	glVertex2f(0.9, -1.0);
	glEnd();


	glColor3f(1.0f, 0.0f, 0.0f);
	// Dessin du polygone
	pol.draw();

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	// Dessin de le fenêtre
	win.draw();


	glFlush();
	/*
	glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0F, 1.0F, 1.0F);

	glBegin(GL_LINE_LOOP);
	glVertex2f(50.0f, 50.0f);
	glVertex2f(100.0f, 50.0f);
	glVertex2f(100.0f, 100.0f);
	glEnd();

	glFlush();
	*/
}

void myInit()
{

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Fenetrage et remplissage");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	//myInit();
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	//glutPassiveMotionFunc(motion);
	glutMainLoop();
	return 0;


	/*
	Vector2 P1(2, 2);
	Vector2 P2(3, 4);
	Vector2 F1(1, 3);
	Vector2 F2(3, 3);
	Vector2 inter;

	intersection(P1, P2, F1, F2, inter);

	std::cout << inter << std::endl;
	*
	
	// Définition du polygone
	Polygon pol;

	Vector2 polA(1, 1);
	Vector2 polB(1, 5);
	Vector2 polC(3, 5);
	Vector2 polD(3, 3);
	Vector2 polE(5, 5);
	Vector2 polF(7, 5);
	Vector2 polG(7, 3);
	Vector2 polH(5, 1);

	pol.add(polA);
	pol.add(polB);
	pol.add(polC);
	pol.add(polD);
	pol.add(polE);
	pol.add(polF);
	pol.add(polG);
	pol.add(polH);

	// Définition de la fenêtre
	Polygon win;

	Vector2 winA(2, 2);
	Vector2 winB(2, 4);
	Vector2 winC(6.5, 4);
	Vector2 winD(6.5, 2);

	win.add(winA);
	win.add(winD);
	win.add(winC);
	win.add(winB);
	win.add(winA);

	// Fenetrage du polygon
	Polygon polWindowed = pol.polygonWindowed(win);

	std::cout << polWindowed << std::endl;
	
	getchar();


	return 0;*/
}