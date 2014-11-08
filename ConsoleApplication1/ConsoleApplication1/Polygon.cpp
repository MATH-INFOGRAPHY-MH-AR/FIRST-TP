/*
Fichier :							Polygon
Date de création :					06/11/2014
Date de dernière modification :		08/11/2014
Auteur:								Alexandre Rivet / Maxime Hélaine
*/
#include "Polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(const std::vector<Vector2> points)
{
	mVectorList = points;
}

Polygon::Polygon(const Polygon& p)
{
	mVectorList = p.mVectorList;
}

Polygon::~Polygon(void) {}

std::vector<Vector2> Polygon::getPoints()
{
	return mVectorList;
}

void Polygon::setPoints(std::vector<Vector2> vl)
{
	mVectorList = vl;
}

Vector2& Polygon::getPointAt(const int i)
{
	return mVectorList[i];
}

void Polygon::add(Vector2& v)
{
	mVectorList.push_back(v);
}

void Polygon::remove(const int i)
{
	mVectorList.erase(mVectorList.begin() + i);
}

int Polygon::getNbVertices() const
{
	return mVectorList.size();
}

bool Polygon::isConvex() const
{
	if (mVectorList.size() < 3)
		return false;

	Vector2 prev, current, next;
	Vector2 firstSide, nextSide;
	float angle;
	for (int i = 1; i < mVectorList.size(); i++)
	{
		prev = mVectorList[i - 1];
		current = mVectorList[i];
		next = (i < mVectorList.size() - 1) ? mVectorList[i + 1] : mVectorList[0];
		firstSide = current - prev;
		nextSide = current - next;
		angle = firstSide.angleOrientedBetween(nextSide);
		if (angle > 180)
			return false;
	}

	return true;
}

bool Polygon::isConcave() const
{
	return !isConvex();
}

Polygon& Polygon::polygonWindowed(Polygon& window)
{
	std::vector<Vector2> listOfPointsPolygon = mVectorList;
	std::vector<Vector2> listOfPointsWindow = window.getPoints();
	std::vector<Vector2> listOfPointsNewPoly;

	int i, j;
	int nbPointsNewWindow;

	Vector2 S, F, I;

	for (i = 1; i < (listOfPointsWindow.size() - 1); i++)
	{
		listOfPointsNewPoly.clear();
		for (j = 1; j < (listOfPointsPolygon.size()); j++)
		{
			if (j == 1)
				F = listOfPointsPolygon[j];
			else
			{
				if (coupe(S, listOfPointsPolygon[j] , listOfPointsWindow[i], listOfPointsWindow[i+1]))
				{
					I = intersections(S, listOfPointsPolygon[j], listOfPointsWindow[i], listOfPointsWindow[i+1]);
					listOfPointsNewPoly.push_back(I);
				}
			}
			S = listOfPointsPolygon[j];
			if (visible(S, listOfPointsWindow[i], listOfPointsWindow[i+1]))
			{
				listOfPointsNewPoly.push_back(S);
			}
		}
	}
	if (listOfPointsNewPoly.size() > 0)
	{
		if(coupe(S, F , listOfPointsWindow[i], listOfPointsWindow[i+1]))
		{
			I = intersection(S, F,  listOfPointsWindow[i], listOfPointsWindow[i+1]);
			listOfPointsNewPoly.push_back(I);
		}
		listOfPointsPolygon = listOfPointsNewPoly;
	}
	return Polygon(listOfPointsNewPoly);
}

bool coupe(Vector2& A, Vector2& B, Vector2& C, Vector2& D)
{
	
	float a1 = (B.getY() - A.getY()) / (B.getX() - A.getX());
	float b1 = A.getY() - (a1 * A.getX());

	float a2 = (D.getY() - C.getY()) / (D.getX() - C.getX());
	float b2 = C.getY() - (a2 * C.getX());

	if (a1 - a2 == 0)
		return false;

	float x = (b2 - b1) / (a1 - a2);

	if (x >= A.getX() && x <= B.getX())
		return true;

	return false;
}

Vector2& intersection(Vector2& A, Vector2& B, Vector2& C, Vector2& D)
{

	float a1 = (B.getY() - A.getY()) / (B.getX() - A.getX());
	float b1 = A.getY() - (a1 * A.getX());

	float a2 = (D.getY() - C.getY()) / (D.getX() - C.getX());
	float b2 = C.getY() - (a2 * C.getX());

	if (a1 - a2 == 0)
		return Vector2();

	float x = (b2 - b1) / (a1 - a2);
	float y = a1 * x + b1;

	if (x >= A.getX() && x <= B.getX())
		return Vector2(x,y);

	return Vector2();
}

bool visible(Vector2& S, Vector2& A, Vector2& B)
{
	Vector2 AB = Vector2(B.getX() - A.getX(), B.getY() - A.getY());
	Vector2 AS = Vector2(S.getX() - A.getX(), S.getY() - A.getY());

	if (AS.getX()*AB.getY() - AS.getY()*AB.getX() > 0)
		return true;

	return false;
}