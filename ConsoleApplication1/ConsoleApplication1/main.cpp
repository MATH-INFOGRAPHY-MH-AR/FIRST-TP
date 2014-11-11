#include "Vector2.h"
#include "Polygon.h"


int main(void)
{
	/*
	Vector2 P1(2, 2);
	Vector2 P2(3, 4);
	Vector2 F1(1, 3);
	Vector2 F2(3, 3);
	Vector2 inter;

	intersection(P1, P2, F1, F2, inter);

	std::cout << inter << std::endl;
	*/
	
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

	return 0;
}