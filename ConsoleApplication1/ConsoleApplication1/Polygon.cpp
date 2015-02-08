/*
Fichier :							Polygon
Date de cr�ation :					06/11/2014
Date de derni�re modification :		04/02/2015
Auteur:								Alexandre Rivet / Maxime H�laine
*/
#include "Polygon.h"

Polygon::Polygon()
{
	mColor = new float[3];
	mColor[0] = 1.0f;
	mColor[1] = 1.0f;
	mColor[2] = 1.0f;
}

Polygon::Polygon(const std::vector<Vector2> points)
{
	mVectorList = points;
	mColor = new float[3];
	mColor[0] = 1.0f;
	mColor[1] = 1.0f;
	mColor[2] = 1.0f;
}

Polygon::Polygon(const Polygon& p)
{
	mVectorList = p.mVectorList;
	mColor = new float[3];
	mColor[0] = 1.0f;
	mColor[1] = 1.0f;
	mColor[2] = 1.0f;
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

float* Polygon::getColor() const
{
	return mColor;
}

void Polygon::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

std::ostream& operator << (std::ostream& os, const Polygon& pol)
{
	for (int i = 0; i < pol.getNbVertices(); i++)
	{
		os << pol.mVectorList[i] << std::endl;
	}

	return os;
}

Vector2& Polygon::getPointAt(const int i)
{
	return mVectorList[i];
}

void Polygon::insert(int index, const Vector2& v)
{
	mVectorList.insert(mVectorList.begin() + index, v);
}

void Polygon::add(const Vector2& v)
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
	for (unsigned int i = 1; i < mVectorList.size(); i++)
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

Polygon Polygon::polygonWindowed(Polygon& window) const
{
	if (mVectorList.size() < 3 || window.getPoints().size() < 3)
	{
		std::cout << "La fenetre et/ou le polygone doivent poss�der au minimum 3 sommets" << std::endl;
		return Polygon(mVectorList);
	}
	
	std::vector<Vector2> pointListInputPolygon = mVectorList;

	std::vector<Vector2> pointListOutputPolygon;
	
	std::vector<Vector2> pointListWindow = window.getPoints();
	pointListWindow.push_back(pointListWindow[0]);
	Vector2 BA = pointListWindow[1] - pointListWindow[0];
	Vector2 BC = pointListWindow[1] - pointListWindow[2];

	if (pointListWindow.size() >= 3 && BA.orientationTriangle(BC) < 0)
		std::reverse(pointListWindow.begin(), pointListWindow.end());

	/*if (window.isConcave())
	{
		std::cout << "La fenetre est concave. Desole je ne sais pas quoi faire..." << std::endl;
		return Polygon();
	}*/

	int i = 0, j = 0;
	int nbPointOutputPolygon = 0;
	int nbPointInputPolygon = pointListInputPolygon.size();
	int nbPointWindow = pointListWindow.size() - 1;

	Vector2 S, F, I, inter;
	
	// Pour chaque point de la window
	for (i = 0; i < nbPointWindow; i++)
	{
		nbPointOutputPolygon = 0;
		pointListOutputPolygon.clear();
		 
		// Pour chaque point du polygone
		for (j = 0; j < nbPointInputPolygon; j++)
		{
			if (j == 0)
			{
				F = pointListInputPolygon[j]; // On sauve le 1er sommet
			}
			else if (intersection(S, pointListInputPolygon[j], pointListWindow[i], pointListWindow[i + 1], inter))
			{
				pointListOutputPolygon.push_back(inter);
				nbPointOutputPolygon++;
			}

			S = pointListInputPolygon[j];
			if (visible(S, pointListWindow[i], pointListWindow[i + 1]))
			{
				pointListOutputPolygon.push_back(S);
				nbPointOutputPolygon++;
			}
		}

		if (nbPointOutputPolygon > 0)
		{
			if (intersection(S, F, pointListWindow[i], pointListWindow[i + 1], inter))
			{
				pointListOutputPolygon.push_back(inter);
				nbPointOutputPolygon++;
			}

			pointListInputPolygon = pointListOutputPolygon;
			nbPointInputPolygon = nbPointOutputPolygon;
		}
	}

	Polygon outputPol(pointListInputPolygon);
	outputPol.removeDuplicateVertices();

	return outputPol;
}

void Polygon::draw() const
{
	glColor3f(mColor[0], mColor[1], mColor[2]);

	if (mVectorList.size() == 1)
		glBegin(GL_POINTS);
	else if (mVectorList.size() == 2)
		glBegin(GL_LINES);
	else
		glBegin(GL_LINE_LOOP);

	Vector2 v;
	for (unsigned int i = 0; i < mVectorList.size(); i++)
	{
		v = mVectorList[i];
		glVertex2f(v.getX(), v.getY());
	}

	glEnd();
}

void Polygon::removeDuplicateVertices()
{
	unsigned int i;
	Vector2 currentVector, nextVector;
	for (i = 0; i < mVectorList.size() - 1; i++)
	{
		currentVector = mVectorList[i];
		nextVector = mVectorList[i + 1];
		if (currentVector == nextVector)
		{
			mVectorList.erase(mVectorList.begin() + (i + 1));
			i--;
		}			
	}
}

void Polygon::reset()
{
	mVectorList.clear();
}

bool Polygon::isInclude(Vector2& A)
{
	if (mVectorList.size() < 3)
		return false;

	Vector2 vector_for_intersection = Vector2(1, 1);
	int nbIntersections = 0;
	for (unsigned int i = 0; i < mVectorList.size() - 1; ++i)
	{
		if (intersectionBetweenSegments(A, vector_for_intersection, mVectorList[i], mVectorList[i + 1]))
		{
			nbIntersections++;
		}
	}

	if (intersectionBetweenSegments(A, vector_for_intersection, mVectorList[mVectorList.size() - 1], mVectorList[0]))
		nbIntersections++;

	return (nbIntersections % 2 == 1) ? true : false;

}

void Polygon::computeFillArea()
{
	mAreaFilled.clear();
	if (mVectorList.size() < 3)
		return;

	// Calcul du rectangle englobant
	float xmin = 500, ymin = 500, xmax = 0, ymax = 0;
	Vector2 tmp;
	for (unsigned int i = 0; i < mVectorList.size(); ++i)
	{
		tmp = mVectorList[i];
		if (tmp.getX() < xmin)
			xmin = tmp.getX();

		if (tmp.getY() < ymin)
			ymin = tmp.getY();

		if (tmp.getX() > xmax)
			xmax = tmp.getX();

		if (tmp.getY() > ymax)
			ymax = tmp.getY();
	}

	for (float x = xmin; x < xmax; x += 1)
	{
		for (float y = ymax; y > ymin; y -= 1)
		{
			Vector2 tmp = Vector2(x, y);
			if (isInclude(tmp))
			{
				mAreaFilled.push_back(tmp);
			}
		}
	}
}

void Polygon::fill()
{
	glColor4f(mColor[0], mColor[1], mColor[2], 0.6f);
	glBegin(GL_POINTS);

	for (unsigned int i = 0; i < mAreaFilled.size(); ++i)	
		glVertex2f(mAreaFilled[i].getX(), mAreaFilled[i].getY());

	glEnd();

}

bool intersection(Vector2& sA, Vector2& sB, Vector2& dA, Vector2& dB, Vector2& inter)
{
	// Equation param�trique d'une droite � partir de deux points
	// P(t) = sA + (sB - sA)t
	// Q(s) = dA + (dB - dA)s
	// ^ * X = b 

	// D�finition de la matrice 2x2 -> ^
	float matrix[2][2];
	matrix[0][0] = sB.getX() - sA.getX();
	matrix[0][1] = dA.getX() - dB.getX();
	matrix[1][0] = sB.getY() - sA.getY();
	matrix[1][1] = dA.getY() - dB.getY();

	// Calcul du d�terminant
	float determinant = (sB.getX() - sA.getX()) * (dA.getY() - dB.getY()) - (sB.getY() - sA.getY()) * (dA.getX() - dB.getX());

	// On quitte si le d�terminant est nul
	if (determinant == 0.0f)
		return false;

	// On calcul l'inverse de la matrice -> ^-1
	float invmatrix[2][2];
	invmatrix[0][0] = matrix[1][1] * (1 / determinant);
	invmatrix[0][1] = -matrix[0][1] * (1 / determinant);
	invmatrix[1][0] = -matrix[1][0] * (1 / determinant);
	invmatrix[1][1] = matrix[0][0] * (1 / determinant);

	// D�finition du b
	float bMatrix[2];
	bMatrix[0] = dA.getX() - sA.getX();
	bMatrix[1] = dA.getY() - sA.getY();

	// R�sultat de la multiplication -> ^-1 * b
	float X[2];
	// correspond � t
	X[0] = invmatrix[0][0] * bMatrix[0] + invmatrix[0][1] * bMatrix[1];

	// correspond � s
	X[1] = invmatrix[1][0] * bMatrix[0] + invmatrix[1][1] * bMatrix[1];

	// t compris entre 0 et 1 du coup le point d'intersection est sur le segment
	if (X[0] >= 0.0f && X[0] <= 1.0f)
	{
		inter = sA + (sB - sA) * X[0];
		return true;
	}
	else
	{
		return false;
	}
}

bool intersectionBetweenSegments(Vector2& sA, Vector2& sB, Vector2& dA, Vector2& dB)
{
	// Equation param�trique d'une droite � partir de deux points
	// P(t) = sA + (sB - sA)t
	// Q(s) = dA + (dB - dA)s
	// ^ * X = b 

	// D�finition de la matrice 2x2 -> ^
	float matrix[2][2];
	matrix[0][0] = sB.getX() - sA.getX();
	matrix[0][1] = dA.getX() - dB.getX();
	matrix[1][0] = sB.getY() - sA.getY();
	matrix[1][1] = dA.getY() - dB.getY();

	// Calcul du d�terminant
	float determinant = (sB.getX() - sA.getX()) * (dA.getY() - dB.getY()) - (sB.getY() - sA.getY()) * (dA.getX() - dB.getX());

	// On quitte si le d�terminant est nul
	if (determinant == 0.0f)
		return false;

	// On calcul l'inverse de la matrice -> ^-1
	float invmatrix[2][2];
	invmatrix[0][0] = matrix[1][1] * (1 / determinant);
	invmatrix[0][1] = -matrix[0][1] * (1 / determinant);
	invmatrix[1][0] = -matrix[1][0] * (1 / determinant);
	invmatrix[1][1] = matrix[0][0] * (1 / determinant);

	// D�finition du b
	float bMatrix[2];
	bMatrix[0] = dA.getX() - sA.getX();
	bMatrix[1] = dA.getY() - sA.getY();

	// R�sultat de la multiplication -> ^-1 * b
	float X[2];
	// correspond � t
	X[0] = invmatrix[0][0] * bMatrix[0] + invmatrix[0][1] * bMatrix[1];

	// correspond � s
	X[1] = invmatrix[1][0] * bMatrix[0] + invmatrix[1][1] * bMatrix[1];

	// t et s compris entre 0 et 1 du coup le point d'intersection est sur les deux segments
	if ((X[0] >= 0.0f && X[0] <= 1.0f) && (X[1] >= 0.0f && X[1] <= 1.0f))
		return true;
	else
		return false;
}

bool visible(Vector2& S, Vector2& A, Vector2& B)
{
	Vector2 AB = B - A;
	Vector2 AS = S - A;

	if (AS.crossProduct(AB) >= 0)
		return true;
	
	return false;
}