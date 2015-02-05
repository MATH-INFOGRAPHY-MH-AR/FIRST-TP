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

	// Dessin des polygones
	for (unsigned int i = 0; i < polygons.size(); ++i)
		polygons[i].draw();

	// Dessin des fenêtres
	for (unsigned int i = 0; i < windows.size(); ++i)
		windows[i].draw();

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
	initMenu();
	//glutMotionFunc(motion);
	//glutPassiveMotionFunc(motion);
	glutMainLoop();
	return 0;
}