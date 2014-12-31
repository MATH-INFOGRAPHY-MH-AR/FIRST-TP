#include <iostream>
#include <GL/glut.h>

#include "Constants.h"
#include "Vector2.h"
#include "FenetreRemplissageInterface.h"


void key(unsigned char k, int x, int y)
{
	switch (k)
	{
		case 'p':					// Tracé du polygone
			state = 0;
			break;
		case 'f':					// Tracé de la fenêtre
			state = 1;
			break;
		case 'a':
			pol = pol.polygonWindowed(win);
			break;
		case 'r':
			pol.reset();
			win.reset();
			break;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		mouseDown(button, x, y);

	else if (state == GLUT_UP)
		mouseUp(button, x, y);
}

void motion(int x, int y)
{
	std::cout << "MOVING " << x << "," << y << std::endl;
}

void mouseDown(int button, int x, int y)
{
	float xF = (float)x / ((float)WINDOW_WIDTH / 2.0) + (-1.0f);
	float yF = - ((float)y / ((float)WINDOW_HEIGHT / 2.0) + (-1.0f));

	if (state == 0)
		pol.add(Vector2(xF, yF));
	else if (state == 1)
		win.add(Vector2(xF, yF));

	glutPostRedisplay();
}

void mouseUp(int button, int x, int y)
{
	
}
