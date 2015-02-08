#ifndef FENETRE_REMPLISSAGE_INTERFACE_H
#define FENETRE_REMPLISSAGE_INTERFACE_H

void key(unsigned char, int, int);
void mouse(int, int, int, int);
void motion(int, int);

void mouseDown(int, int, int);
void mouseUp(int, int, int);

void initMenu();
void updateMenu();

void select(int selection);
void selectPolygon(int selection);
void selectWindow(int selection);
void selectFillMode(int selection);
void selectWindowMode(int selection);
void editPolygon(int selection);
void addPolygonItem(int parent, int index);
void setColor(int selection);

#endif