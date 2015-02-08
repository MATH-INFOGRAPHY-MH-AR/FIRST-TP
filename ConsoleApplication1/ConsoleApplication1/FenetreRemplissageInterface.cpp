#include <iostream>
#include <string>

#include <GL/glut.h>

#include "Constants.h"
#include "Vector2.h"
#include "FenetreRemplissageInterface.h"

// Fonction appelée par le clavier
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
		case 27:											// ECHAP => Quitte l'édition du polygone en cours
			WINDOW_OR_POLYGON_EDITED = -1;
			CURRENT_POLYGON_EDITED = -1;
			CURRENT_VERTEX_EDITED = 0;

		case 127:											// Supprime le vertex sélectionné en cours 
			if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
			{
				if (CURRENT_VERTEX_EDITED >= 1)
				{
					polygons[CURRENT_POLYGON_EDITED]->remove(CURRENT_VERTEX_EDITED - 1);
					polygons[CURRENT_POLYGON_EDITED]->computeFillArea();
					
					if (CURRENT_VERTEX_EDITED > polygons[CURRENT_POLYGON_EDITED]->getNbVertices())
						CURRENT_VERTEX_EDITED = polygons[CURRENT_POLYGON_EDITED]->getNbVertices();
				}
			}
			else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
			{
				if (CURRENT_VERTEX_EDITED >= 1)
				{
					windows[CURRENT_POLYGON_EDITED]->remove(CURRENT_VERTEX_EDITED - 1);
					windows[CURRENT_POLYGON_EDITED]->computeFillArea();

					if (CURRENT_VERTEX_EDITED > polygons[CURRENT_POLYGON_EDITED]->getNbVertices())
						CURRENT_VERTEX_EDITED = polygons[CURRENT_POLYGON_EDITED]->getNbVertices();
				}
			}
			break;
	}

	glutPostRedisplay();
}

// Fonction appelée pour toute action de la souris (UP & DOWN)
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		mouseDown(button, x, y);

	else if (state == GLUT_UP)
		mouseUp(button, x, y);
}

// Fonction appelée lorsque l'on bouge la souris
void motion(int x, int y)
{
	float xF = x;
	float yF = y;

	// Drag sur le clic molette
	if (MIDDLE_BUTTON_PRESSED)
	{
		if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
		{
			if (CURRENT_VERTEX_EDITED >= 0 && CURRENT_VERTEX_EDITED <= polygons[CURRENT_POLYGON_EDITED]->getNbVertices() )
			{
				Vector2 currentPoint = polygons[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);
				float distance = currentPoint.distance(Vector2(xF, yF));
				if (distance < 10)
				{
					polygons[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setX(xF);
					polygons[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setY(yF);
				}
			} 
		}
		else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
		{
			if (CURRENT_VERTEX_EDITED >= 0 && CURRENT_VERTEX_EDITED <= windows[CURRENT_POLYGON_EDITED]->getNbVertices())
			{
				Vector2 currentPoint = windows[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1);
				float distance = currentPoint.distance(Vector2(xF, yF));
				if (distance < 10)
				{
					windows[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setX(xF);
					windows[CURRENT_POLYGON_EDITED]->getPointAt(CURRENT_VERTEX_EDITED - 1).setY(yF);
				}
			}
		}
	}

	glutPostRedisplay();
}

// Fonction appelée lorsque l'on enfonce un bouton de la souris
void mouseDown(int button, int x, int y)
{
	float xF = x;
	float yF = y;

	// Clic gauche => Ajout d'un nouveau point dans le polygone en cours (soit à la fin soit insertion à l'espace en cours
	if (button == GLUT_LEFT_BUTTON)
	{
		if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
		{
			if (CURRENT_VERTEX_EDITED == polygons[CURRENT_POLYGON_EDITED]->getNbVertices())
				polygons[CURRENT_POLYGON_EDITED]->add(Vector2(xF, yF));
			else
				polygons[CURRENT_POLYGON_EDITED]->insert(CURRENT_VERTEX_EDITED, Vector2(xF, yF));			
			polygons[CURRENT_POLYGON_EDITED]->computeFillArea();
		}
			
		else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
		{
			if (CURRENT_VERTEX_EDITED == windows[CURRENT_POLYGON_EDITED]->getNbVertices())
				windows[CURRENT_POLYGON_EDITED]->add(Vector2(xF, yF));
			else
				windows[CURRENT_POLYGON_EDITED]->insert(CURRENT_VERTEX_EDITED, Vector2(xF, yF));
			windows[CURRENT_POLYGON_EDITED]->computeFillArea();
		}
		CURRENT_VERTEX_EDITED++;
	}

	// Clic molette:
	// - Début de drag
	// - Calcul du point le plus proche pour savoir quel point on édite
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		MIDDLE_BUTTON_PRESSED = true;

		float distance = 1000.0;
		if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
		{
			unsigned int size = polygons[CURRENT_POLYGON_EDITED]->getNbVertices();
			for (unsigned int i = 0; i < size; ++i)
			{
				Vector2 currentPoint = polygons[CURRENT_POLYGON_EDITED]->getPointAt(i);
				float currentDistance = currentPoint.distance(Vector2(xF, yF));
				if (currentDistance < distance)
				{
					distance = currentDistance;
					CURRENT_VERTEX_EDITED = (i + 1);
				}
			}
		}
		else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
		{
			unsigned int size = windows[CURRENT_POLYGON_EDITED]->getNbVertices();
			for (unsigned int i = 0; i < size; ++i)
			{
				Vector2 currentPoint = windows[CURRENT_POLYGON_EDITED]->getPointAt(i);
				float currentDistance = currentPoint.distance(Vector2(xF, yF));
				if (currentDistance < distance)
				{
					distance = currentDistance;
					CURRENT_VERTEX_EDITED = (i + 1);
				}
			}
		}
	}

	glutPostRedisplay();
}

// Fonction appelée lorsque l'on relâche un bouton de la souris
void mouseUp(int button, int x, int y)
{
	// Fin de drag qui permet de mettre à jour le remplissage
	if (button == GLUT_MIDDLE_BUTTON)
	{
		MIDDLE_BUTTON_PRESSED = false;
		if (WINDOW_OR_POLYGON_EDITED == 1 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < polygons.size())
		{
			polygons[CURRENT_POLYGON_EDITED]->computeFillArea();
		}
		else if (WINDOW_OR_POLYGON_EDITED == 2 && CURRENT_POLYGON_EDITED >= 0 && CURRENT_POLYGON_EDITED < windows.size())
		{
			windows[CURRENT_POLYGON_EDITED]->computeFillArea();
		}
	}

	glutPostRedisplay();
}

// Initialisation du menu principal
void initMenu()
{
	// Menu Polygone
	int polygonMenu = glutCreateMenu(selectPolygon);
	glutAddMenuEntry("New", 11);

	// Menu Fenêtre
	int windowMenu = glutCreateMenu(selectWindow);
	glutAddMenuEntry("New", 21);

	// Menu Choix du Remplissage
	int fillMod = glutCreateMenu(selectFillMode);
	glutAddMenuEntry("Method 1", 31);
	glutAddMenuEntry("Method 2", 32);

	// Menu Choix du Fenetrage
	int windowMod = glutCreateMenu(selectWindowMode);
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

// // Fonction appelée pour ouvrir le menu principal
void select(int selection)
{
	switch (selection)
	{
		case 5:
			exit(0);
	}
}

// Fonction appelée pour ouvrir le menu des polygons
void selectPolygon(int selection)
{
	switch (selection)
	{
		case 11:
			addPolygonItem(1, polygons.size());		// Met à jour l'UI
			polygons.push_back(new Polygon());		// Ajoute dans la liste un nouveau polygone

			// Mise à jour des variables globales
			WINDOW_OR_POLYGON_EDITED = 1;
			CURRENT_POLYGON_EDITED = polygons.size() - 1;
			CURRENT_VERTEX_EDITED = 0;

			break;
	}
}

// Fonction appelée pour ouvrir le menu des windows
void selectWindow(int selection)
{
	switch (selection)
	{
		case 21:
			addPolygonItem(2, windows.size());		// Met à jour l'UI
			windows.push_back(new Polygon());		// Ajoute dans la liste un nouveau polygone
	
			// Mise à jour des variables globales
			WINDOW_OR_POLYGON_EDITED = 2;
			CURRENT_POLYGON_EDITED = windows.size() - 1;
			CURRENT_VERTEX_EDITED = 0;

			break;
	}
}

// Fonction appelée pour choisir le mode de remplissage
void selectFillMode(int selection)
{

}

// Fonction appelée pour choisir le mode de fenêtrage
void selectWindowMode(int selection)
{
	switch (selection)
	{
		case 41:
			SHOW_HIDE_OUTPUT_POLYGONS = true;
			break;
		case 42:
			SHOW_HIDE_OUTPUT_POLYGONS = false;
			break;
	}
	glutPostRedisplay();
}

// Fonction appelée lors de la sélection d'un polygone
void editPolygon(int selection)
{
	int win_pol_edited = selection / 100;
	int item_selected = (selection / 10) % 10;
	int polygon_selected = item_selected - 2;
	int edition_selected = selection % 10;

	switch (edition_selected)
	{
		case 2:													// Edition				
			WINDOW_OR_POLYGON_EDITED = win_pol_edited;
			CURRENT_POLYGON_EDITED = polygon_selected;

			if (WINDOW_OR_POLYGON_EDITED == 1)
				CURRENT_VERTEX_EDITED = polygons[CURRENT_POLYGON_EDITED]->getNbVertices();
			else if (WINDOW_OR_POLYGON_EDITED == 2)
				CURRENT_VERTEX_EDITED = windows[CURRENT_POLYGON_EDITED]->getNbVertices();

			glutPostRedisplay();
			break;
		case 3:													// Suppression
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

			// Remise à 0 des états des variables si on supprime le polygone qui est en cours d'édition
			if (win_pol_edited == WINDOW_OR_POLYGON_EDITED && polygon_selected == CURRENT_POLYGON_EDITED)
			{
				WINDOW_OR_POLYGON_EDITED = -1;
				CURRENT_POLYGON_EDITED = -1;
				CURRENT_VERTEX_EDITED = 0;
			}			
			break;
	}

}

// Ajoute un menu item au menu des polygones ou windows
void addPolygonItem(int parent, int index)
{
	std::string prefix = (parent == 1) ? "Polygon_" : "Window_"; 
	int base = parent * 100 + (20 + index * 10) + 1;
	int color_base = base * 10 + 1;

	// Crée le menu de couleur
	int color_tmp = glutCreateMenu(setColor);
	glutAddMenuEntry("Blue", color_base++);
	glutAddMenuEntry("Green", color_base++);
	glutAddMenuEntry("Red", color_base++);
	glutAddMenuEntry("White", color_base++);
	glutAddMenuEntry("Yellow", color_base++);

	// Crée le sous menu du polygone en cours
	int polygon_tmp = glutCreateMenu(editPolygon);
	glutAddSubMenu("Color", color_tmp);
	glutAddMenuEntry("Edit", ++base);
	glutAddMenuEntry("Remove", ++base);

	// Ajout le menu au polygone
	glutSetMenu(parent);
	glutAddSubMenu((prefix + std::to_string(index + 1)).c_str(), polygon_tmp);
}

// Fonction appelée pour le choix d'une couleur
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
				polygons[polygon_selected]->setColor(0.0f, 0.0f, 1.0f);
			else
				windows[polygon_selected]->setColor(0.0f, 0.0f, 1.0f);
			break;
		case 2:											// Green
			if (win_pol_edited == 1)
				polygons[polygon_selected]->setColor(0.0f, 1.0f, 0.0f);
			else
				windows[polygon_selected]->setColor(0.0f, 1.0f, 0.0f);
			break;
		case 3:											// Red
			if (win_pol_edited == 1)
				polygons[polygon_selected]->setColor(1.0f, 0.0f, 0.0f);
			else
				windows[polygon_selected]->setColor(1.0f, 0.0f, 0.0f);
			break;
		case 4:											// Yellow
			if (win_pol_edited == 1)
				polygons[polygon_selected]->setColor(1.0f, 1.0f, 1.0f);
			else
				windows[polygon_selected]->setColor(1.0f, 1.0f, 1.0f);
			break;
		case 5:											// White
			if (win_pol_edited == 1)
				polygons[polygon_selected]->setColor(1.0f, 1.0f, 0.0f);
			else
				windows[polygon_selected]->setColor(1.0f, 1.0f, 0.0f);
			break;
	}

	glutPostRedisplay();
}

void calcAllPolygonWindowed()
{
	outputPolygons.clear();

	unsigned int nbPolygons = polygons.size();
	unsigned int nbWindows = windows.size();

	Polygon output;
	for (unsigned int i = 0; i < nbPolygons; ++i)
	{
		Polygon* p = polygons[i];
		for (unsigned int j = 0; j < nbWindows; ++j)
		{
			Polygon* w = windows[j];
			
			if (j == 0)
				output = Polygon(*p);

			output = output.polygonWindowed(Polygon(*w));
		}
		outputPolygons.push_back(new Polygon(output));		
	}

}