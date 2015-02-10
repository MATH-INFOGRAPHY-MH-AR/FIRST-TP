#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "LCAStruct.h"
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
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	// Clear de la zone de dessin
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	Polygon p;
	p.add(Vector2(30, 50));
	p.add(Vector2(150, 10));
	p.add(Vector2(270, 90));
	p.add(Vector2(270, 190));
	p.add(Vector2(120, 120));
	p.add(Vector2(30, 160));
	p.computeTemporaryStructure();
	p.draw();
	p.fill();
	*/

	// Dessin des polygones
	for (unsigned int i = 0; i < polygons.size(); ++i)
	{
		polygons[i]->draw();
		polygons[i]->fillLines();
	}

	// Dessin des fen�tres
	for (unsigned int i = 0; i < windows.size(); ++i)
	{
		windows[i]->draw();
		windows[i]->fillLines();
	}

	if (SHOW_HIDE_OUTPUT_POLYGONS)
	{
		// Calcul du fen�trage et du remplissage LCA
		calcAllPolygonWindowed();
		computeAllPolygonWindowedLCA();

		// Dessin du r�sultat de fen�trage
		for (unsigned int i = 0; i < outputPolygons.size(); ++i)
		{
			outputPolygons[i]->draw();
			outputPolygons[i]->fillPoints();
		}
	}	

	// Dessin du carr� d'�dition
	if (WINDOW_OR_POLYGON_EDITED != -1)
	{
		Vector2 vector_tmp;
		if (WINDOW_OR_POLYGON_EDITED == 1 && (CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size()) && (CURRENT_VERTEX_EDITED >= 1 && CURRENT_VERTEX_EDITED <= polygons[CURRENT_POLYGON_EDITED]->getNbVertices()))
			vector_tmp = polygons[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);
		if (WINDOW_OR_POLYGON_EDITED == 2 && (CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size()) && (CURRENT_VERTEX_EDITED >= 1 && CURRENT_VERTEX_EDITED <= windows[CURRENT_POLYGON_EDITED]->getNbVertices()))
			vector_tmp = windows[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2f(vector_tmp.getX() - 5, vector_tmp.getY() - 5);
		glVertex2f(vector_tmp.getX() + 5, vector_tmp.getY() - 5);
		glVertex2f(vector_tmp.getX() + 5, vector_tmp.getY() + 5);
		glVertex2f(vector_tmp.getX() - 5, vector_tmp.getY() + 5);
		glEnd();
	}

	glFlush();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Fenetrage et remplissage");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	initMenu();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glEnable(GLUT_MULTISAMPLE);
	// glEnable(GL_LINE_SMOOTH);

	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);	

	glutMainLoop();
	return 0;
}