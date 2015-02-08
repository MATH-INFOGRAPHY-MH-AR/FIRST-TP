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
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
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
}

void display()
{
	// Clear de la zone de dessin
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Dessin des polygones
	for (unsigned int i = 0; i < polygons.size(); ++i)
	{
		polygons[i]->draw();
		polygons[i]->fill();
	}
		

	// Dessin des fenêtres
	for (unsigned int i = 0; i < windows.size(); ++i)
	{
		windows[i]->draw();
		windows[i]->fill();
	}
		

	// Dessin du carré d'édition
	if (WINDOW_OR_POLYGON_EDITED != -1)
	{
		Vector2 vector_tmp;
		if (WINDOW_OR_POLYGON_EDITED == 1 && (CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size()) && (CURRENT_VERTEX_EDITED >= 1 && CURRENT_VERTEX_EDITED <= polygons[CURRENT_POLYGON_EDITED]->getNbVertices()))
			vector_tmp = polygons[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);
		if (WINDOW_OR_POLYGON_EDITED == 2 && (CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size()) && (CURRENT_VERTEX_EDITED >= 1 && CURRENT_VERTEX_EDITED <= windows[CURRENT_POLYGON_EDITED]->getNbVertices()))
			vector_tmp = windows[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2f(vector_tmp.getX() - 0.02, vector_tmp.getY() - 0.02);
		glVertex2f(vector_tmp.getX() + 0.02, vector_tmp.getY() - 0.02);
		glVertex2f(vector_tmp.getX() + 0.02, vector_tmp.getY() + 0.02);
		glVertex2f(vector_tmp.getX() - 0.02, vector_tmp.getY() + 0.02);
		glEnd();
	}

	glFlush();
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
	initMenu();
	
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	

	glutMainLoop();
	return 0;
}