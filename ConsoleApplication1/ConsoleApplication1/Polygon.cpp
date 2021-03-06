/*
Fichier :							Polygon
Date de cr�ation :					06/11/2014
Date de derni�re modification :		04/02/2015
Auteur:								Alexandre Rivet / Maxime H�laine
*/
#include "include/Polygon.h"

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
		return Polygon();
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

	Polygon outputPol(pointListOutputPolygon);
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
	if (mVectorList.size() == 0)
		return;

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

	Vector2 vector_for_intersection = Vector2(500, 500);
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
	mAreaFilledPoints.clear();
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

	for (float x = xmin; x < xmax; ++x)
	{
		for (float y = ymax; y > ymin; --y)
		{
			Vector2 tmp = Vector2(x, y);
			if (isInclude(tmp))
			{
				mAreaFilledPoints.push_back(tmp);
			}
		}
	}
}

void Polygon::computeLCAStructure()
{
	// On reset la liste des lignes � dessiner
	mAreaFilledLines.clear();
	if (mVectorList.size() < 3)
		return;

	// Calcul du rectangle englobant
	int xmin = 500, ymin = 500, xmax = 0, ymax = 0;
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

	// std::cout << abs(ymax - ymin) + 2 << std::endl;

	std::vector<std::list<LCAStruct>> temporaryStructure(abs(ymax - ymin) + 2); // Prise en compte des deux bornes

	// Calcul de la SI
	for (std::vector<Vector2>::iterator it = mVectorList.begin(); it != mVectorList.end() - 1; ++it)
	{
		Vector2 current = *it;
		Vector2 next = *(it + 1);

		int cX = current.getX(), cY = current.getY(), nX = next.getX(), nY = next.getY();

		current = Vector2(cX, cY);
		next = Vector2(nX, nY);

		// std::cout << current << " " << next << std::endl;

		if (next.getY() == current.getY())
			continue;

		int y =(int) (std::min(current.getY(), next.getY()) - ymin);		// Pour retomber dans les index du vector
		float coeff = (next.getX() - current.getX() != 0) ? (float)(next.getY() - current.getY()) / (float)(next.getX() - current.getX()) : 0;

		// std::cout << coeff << std::endl;

		LCAStruct lca;
		lca.ymax = (int) std::max(current.getY(), next.getY());
		lca.ymin = (int) std::min(current.getY(), next.getY());
		lca.xmax = (int) (lca.ymin == current.getY()) ? next.getX() : current.getX();
		lca.xmin = (int) ((lca.ymax == current.getY()) ? next.getX() : current.getX());
		
		lca.coeffInversed = (coeff != 0) ? (1 / coeff) : 0;
		temporaryStructure[y].push_back(lca);
	}

	// Dernier traitement entre le dernier et le premier point du polygone
	Vector2 current = mVectorList[mVectorList.size() - 1];
	Vector2 next = mVectorList[0];
	int cX = current.getX(), cY = current.getY(), nX = next.getX(), nY = next.getY();
	current = Vector2(cX, cY);
	next = Vector2(nX, nY);

	if (next.getY() != current.getY())
	{
		int y = std::min(current.getY(), next.getY()) - ymin;		// Pour retomber dans les index du vector
		float coeff = (next.getX() - current.getX() != 0) ? (next.getY() - current.getY()) / (next.getX() - current.getX()) : 0;

		LCAStruct lca;
		lca.ymax = (int) std::max(current.getY(), next.getY());
		lca.ymin = (int) std::min(current.getY(), next.getY());
		lca.xmax = (int) (lca.ymin == current.getY()) ? next.getX() : current.getX();
		lca.xmin = (int) ((lca.ymax == current.getY()) ? next.getX() : current.getX());

		lca.coeffInversed = (coeff != 0) ? 1 / coeff : 0;
		temporaryStructure[y].push_back(lca);
	}	

	/*
		DEBUT DEBUG SI
	*
	int j = ymin;
	for (std::vector<std::list<LCAStruct>>::iterator it = temporaryStructure.begin(); it != temporaryStructure.end(); ++it)
	{
		std::cout << j;
		for (std::list<LCAStruct>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt)
		{
			std::cout << " => " << (*jt).ymax << " | " << (*jt).xmin << " | " << (*jt).coeffInversed;
		}
		std::cout << std::endl;
		++j;
	}
	/*
		FIN DEBUG SI
	*/

	// Partie parcours
	int y = ymin;
	std::list<LCAStruct> lca_active;
	for (std::vector<std::list<LCAStruct>>::iterator it = temporaryStructure.begin(); it != temporaryStructure.end(); ++it)
	{
		// Ajout des nouveaux maillons
		if ((*it).size() > 0)
			lca_active.insert(lca_active.end(), it->begin(), it->end());

		// Suppression de ceux atteints
		std::list<LCAStruct>::iterator i = lca_active.begin();
		while (i != lca_active.end())
		{
			if (y == i->ymax)
				lca_active.erase(i++);
			else
				++i;
		}

		// Tri de la liste
		lca_active.sort(compareXMin);

		/*
			DEBUT DEBUG LCA_ACTIF
		*
		for (std::list<LCAStruct>::iterator jt = lca_active.begin(); jt != lca_active.end(); ++jt)
		{
			std::cout << " => " << (*jt).ymax << " | " << (*jt).xmin << " | " << (*jt).coeffInversed;
		}
		std::cout << std::endl;
		/*
			FIN DEBUG LCA_ACTIF
		*/

		// std::cout << "Y: " << y << " " << lca_active.size() << std::endl;

		// Enregistrement des lignes
		for (std::list<LCAStruct>::iterator jt = lca_active.begin(); jt != lca_active.end(); ++jt)
		{
			// std::cout << "MAX:" << (*jt).ymax << std::endl;
			Line l;
			l.start = Vector2((*jt).xmin, y);
			++jt;
			l.end = Vector2((*jt).xmin, y);
			mAreaFilledLines.push_back(l);		
		}		

		// Mise � jour des x
		for (std::list<LCAStruct>::iterator jt = lca_active.begin(); jt != lca_active.end(); ++jt)
			(*jt).xmin += (*jt).coeffInversed;
		
		// Incr�ment du y
		++y;
	}
}

void Polygon::fillPoints()
{
	glColor4f(mColor[0], mColor[1], mColor[2], 0.5f);

	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < mAreaFilledPoints.size(); ++i)
		glVertex2f(mAreaFilledPoints[i].getX(), mAreaFilledPoints[i].getY());
	glEnd();
}

void Polygon::fillLines(bool stepByStep)
{
	glColor4f(mColor[0], mColor[1], mColor[2], 0.5f);

	if (!stepByStep)
	{
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < mAreaFilledLines.size(); ++i)
		{
			glVertex2f(mAreaFilledLines[i].start.getX(), mAreaFilledLines[i].start.getY());
			glVertex2f(mAreaFilledLines[i].end.getX(), mAreaFilledLines[i].end.getY());
		}
		glEnd();
	}
	else
	{
		std::cout << "Start STEP_BY_STEP" << std::endl;
		for (unsigned int i = 0; i < mAreaFilledLines.size(); ++i)
		{
			glBegin(GL_LINES);
			glVertex2f(mAreaFilledLines[i].start.getX(), mAreaFilledLines[i].start.getY());
			glVertex2f(mAreaFilledLines[i].end.getX(), mAreaFilledLines[i].end.getY());
			glEnd();
			glFlush();
			std::cin.ignore();
		}
		std::cout << "End STEP_BY_STEP" << std::endl;
	}	
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
	return (AS.crossProduct(AB) >= 0);

	// Vector2 normal = AB.normal();
	// return (normal.dotProduct(AS) >= 0);
}