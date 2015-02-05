#include <iostream>
#include <string>

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
	if (button == GLUT_LEFT_BUTTON)
	{
		float xF = (float)x / ((float)WINDOW_WIDTH / 2.0) + (-1.0f);
		float yF = -((float)y / ((float)WINDOW_HEIGHT / 2.0) + (-1.0f));

		if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
			polygons[CURRENT_POLYGON_EDITED].add(Vector2(xF, yF));
		else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
			windows[CURRENT_POLYGON_EDITED].add(Vector2(xF, yF));
	}


	/*
	if (button == GLUT_RIGHT_BUTTON)
		return;

	float xF = (float)x / ((float)WINDOW_WIDTH / 2.0) + (-1.0f);
	float yF = - ((float)y / ((float)WINDOW_HEIGHT / 2.0) + (-1.0f));

	if (state == 0)
		pol.add(Vector2(xF, yF));
	else if (state == 1)
		win.add(Vector2(xF, yF));
	*/

	glutPostRedisplay();
}

void mouseUp(int button, int x, int y)
{
	
}



void initMenu()
{
	// Menu Polygone
	int polygonMenu = glutCreateMenu(selectPolygon);
	glutAddMenuEntry("New", 11);

	// Menu Fenêtre
	int windowMenu = glutCreateMenu(selectWindow);
	glutAddMenuEntry("New", 21);

	// Menu Choix du Remplissage
	int fillMod = glutCreateMenu(selectFillMod);
	glutAddMenuEntry("Method 1", 31);
	glutAddMenuEntry("Method 2", 32);

	// Menu Choix du Fenetrage
	int windowMod = glutCreateMenu(selectWindowMod);
	glutAddMenuEntry("Show", 41);
	glutAddMenuEntry("Hide", 42);

	// Menu principal 
	glutCreateMenu(select);
	glutAddSubMenu("Polygon", polygonMenu);
	glutAddSubMenu("Window", windowMenu);
	glutAddSubMenu("Fill Mod", fillMod);
	glutAddSubMenu("Window Mod", windowMod);
	glutAddMenuEntry("Quitter", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void select(int selection)
{
	std::cout << selection;
}

void selectPolygon(int selection)
{
	switch (selection)
	{
		case 11:
			addPolygonItem(1, polygons.size());
			polygons.push_back(Polygon());

			WINDOW_OR_POLYGON_EDITED = 1;
			CURRENT_POLYGON_EDITED = polygons.size() - 1;

			break;
	}
}

void selectWindow(int selection)
{
	switch (selection)
	{
		case 21:
			addPolygonItem(2, windows.size());
			windows.push_back(Polygon());
	
			WINDOW_OR_POLYGON_EDITED = 2;
			CURRENT_POLYGON_EDITED = windows.size() - 1;
	
			break;
	}
}

void selectFillMod(int selection)
{

}

void selectWindowMod(int selection)
{

}

void editPolygon(int selection)
{
	int win_pol_edited = selection / 100;
	int item_selected = (selection / 10) % 10;
	int polygon_selected = item_selected - 2;
	int edition_selected = selection % 10;

	switch (edition_selected)
	{
		case 2:					
			WINDOW_OR_POLYGON_EDITED = win_pol_edited;
			CURRENT_POLYGON_EDITED = polygon_selected;
			break;
		case 3:	
			// Supprime les menu items
			switch (win_pol_edited)
			{
			case 1:
				glutSetMenu(win_pol_edited);
				for (unsigned int i = 0; i < polygons.size(); ++i)
					glutRemoveMenuItem(2);

				// Met à jour la liste de polygons
				polygons.erase(polygons.begin() + polygon_selected);

				// Recrée les MenuItem
				for (unsigned int i = 0; i < polygons.size(); ++i)
					addPolygonItem(win_pol_edited, i);
				break;
			case 2:
				glutSetMenu(win_pol_edited);
				for (unsigned int i = 0; i < windows.size(); ++i)
					glutRemoveMenuItem(2);

				// Met à jour la liste de polygons
				windows.erase(windows.begin() + polygon_selected);

				// Recrée les MenuItem
				for (unsigned int i = 0; i < windows.size(); ++i)
					addPolygonItem(win_pol_edited, i);
				break;
			}
			glutPostRedisplay();
			break;
	}

}

void addPolygonItem(int parent, int index)
{
	std::string prefix = (parent == 1) ? "Polygon_" : "Window_"; 
	int base = parent * 100 + (20 + index * 10) + 1;
	int color_base = base * 10 + 1;

	int color_tmp = glutCreateMenu(setColor);
	glutAddMenuEntry("Blue", color_base++);
	glutAddMenuEntry("Green", color_base++);
	glutAddMenuEntry("Red", color_base++);
	glutAddMenuEntry("White", color_base++);
	glutAddMenuEntry("Yellow", color_base++);

	int polygon_tmp = glutCreateMenu(editPolygon);
	glutAddSubMenu("Color", color_tmp);
	glutAddMenuEntry("Edit", ++base);
	glutAddMenuEntry("Remove", ++base);

	glutSetMenu(parent);
	glutAddSubMenu((prefix + std::to_string(index + 1)).c_str(), polygon_tmp);
}

void setColor(int selection)
{
	int win_pol_edited = selection / 1000;
	int item_selected = (selection / 100) % 10;
	int polygon_selected = item_selected - 2;
	int color = selection % 10;

	switch (color)
	{
		case 1:											// Blue
			if (win_pol_edited == 1)
				polygons[polygon_selected].setColor(0.0f, 0.0f, 1.0f);
			else
				windows[polygon_selected].setColor(0.0f, 0.0f, 1.0f);
			break;
		case 2:											// Green
			if (win_pol_edited == 1)
				polygons[polygon_selected].setColor(0.0f, 1.0f, 0.0f);
			else
				windows[polygon_selected].setColor(0.0f, 1.0f, 0.0f);
			break;
		case 3:											// Red
			if (win_pol_edited == 1)
				polygons[polygon_selected].setColor(1.0f, 0.0f, 0.0f);
			else
				windows[polygon_selected].setColor(1.0f, 0.0f, 0.0f);
			break;
		case 4:											// Yellow
			if (win_pol_edited == 1)
				polygons[polygon_selected].setColor(1.0f, 1.0f, 1.0f);
			else
				windows[polygon_selected].setColor(1.0f, 1.0f, 1.0f);
			break;
		case 5:											// White
			if (win_pol_edited == 1)
				polygons[polygon_selected].setColor(1.0f, 1.0f, 0.0f);
			else
				windows[polygon_selected].setColor(1.0f, 1.0f, 0.0f);
			break;
	}

	glutPostRedisplay();
}