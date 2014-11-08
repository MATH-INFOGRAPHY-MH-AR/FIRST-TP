/*
Fichier :							Polygon
Date de cr�ation :					06/11/2014
Date de derni�re modification :		08/11/2014
Auteur:								Alexandre Rivet / Maxime H�laine
*/
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

	Vector2& getPointAt(const int);
	void add(Vector2&);
	void remove(const int);
	int getNbVertices() const;

	bool isConcave() const;
	bool isConvex() const;

	Polygon& polygonWindowed(Polygon& window);

private:
	std::vector<Vector2> mVectorList;
};

bool coupe(Vector2& A, Vector2& B, Vector2& C, Vector2& D);
Vector2& intersections(Vector2& A, Vector2& B, Vector2& C, Vector2& D);
bool visible(Vector2& S,  Vector2& A, Vector2& B);