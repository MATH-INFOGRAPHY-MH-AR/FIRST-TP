#ifndef POLYGON_H 
#define POLYGON_H
/*
Fichier :							Polygon
Date de création :					06/11/2014
Date de dernière modification :		11/11/2014
Auteur:								Alexandre Rivet / Maxime Hélaine
*/

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "Vector2.h"

class Polygon
{
public:
	Polygon();
	Polygon(const std::vector<Vector2>);
	Polygon(const Polygon&);
	~Polygon(void);

	std::vector<Vector2> getPoints();
	void setPoints(std::vector<Vector2>);

	float* getColor() const;
	void setColor(float, float, float);

	// Méthode d'affichage (notamment pour le debug)
	friend std::ostream& operator << (std::ostream&, const Polygon&);

	Vector2& getPointAt(const int);
	void add(const Vector2&);
	void remove(const int);
	int getNbVertices() const;
	void removeDuplicateVertices();
	void reset();

	bool isConcave() const;
	bool isConvex() const;

	Polygon polygonWindowed(Polygon& window) const;

	void draw() const;

private:
	std::vector<Vector2> mVectorList;
	float* mColor;

	float mRed;
	float mGreen;
	float mBlue;
};

bool intersection(Vector2& sA, Vector2& sB, Vector2& dA, Vector2& dB, Vector2& inter);
bool visible(Vector2& S,  Vector2& A, Vector2& B);

#endif