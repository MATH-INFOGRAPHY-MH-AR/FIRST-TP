#include <stdlib.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "include/LCAStruct.h"
#include "include/Constants.h"
#include "include/Vector2.h"
#include "include/Polygon.h"
#include "include/FenetreRemplissageInterface.h"

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

	// Dessin des polygones
	for (unsigned int i = 0; i < polygons.size(); ++i)
	{
		polygons[i]->draw();

		if (CURRENT_LCA_SHOWN == 1 || CURRENT_LCA_SHOWN == 2)
			polygons[i]->fillLines(CURRENT_STEP_BY_STEP_CHOSEN);
	}

	// Dessin des fenêtres
	for (unsigned int i = 0; i < windows.size(); ++i)
	{
		windows[i]->draw();

		if (CURRENT_LCA_SHOWN == 1 || CURRENT_LCA_SHOWN == 2)
			windows[i]->fillLines(CURRENT_STEP_BY_STEP_CHOSEN);
	}

	// Affichage du fenêtrage
	if (SHOW_HIDE_OUTPUT_POLYGONS)
	{
		// Calcul du fenêtrage et du remplissage LCA
		calcAllPolygonWindowed();
		computeAllPolygonWindowedLCA();

		// Dessin du résultat de fenêtrage
		for (unsigned int i = 0; i < outputPolygons.size(); ++i)
		{
			outputPolygons[i]->draw();

			if (CURRENT_LCA_SHOWN == 1 || CURRENT_LCA_SHOWN == 3)
				outputPolygons[i]->fillLines(CURRENT_STEP_BY_STEP_CHOSEN);
		}
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
	/*
	polygons.push_back(new Polygon());
	polygons[0]->setColor(0, 0, 1);
	polygons[0]->add(Vector2(107, 108));
	polygons[0]->add(Vector2(305, 100));
	polygons[0]->add(Vector2(300, 356));
	polygons[0]->add(Vector2(100, 300));
	polygons[0]->computeLCAStructure();

	windows.push_back(new Polygon());
	windows[0]->setColor(0, 1, 0);
	windows[0]->add(Vector2(50, 200));
	windows[0]->add(Vector2(200, 50));
	windows[0]->add(Vector2(350, 200));
	windows[0]->computeLCAStructure();
	*/

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