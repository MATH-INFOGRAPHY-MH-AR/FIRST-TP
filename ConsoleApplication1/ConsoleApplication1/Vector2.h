/*
Fichier :							Vector2
Date de création :					05/11/2014
Date de dernière modification :		06/11/2014
Auteur:								Alexandre Rivet
*/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

class Vector2
{
public:
	// Constructeur et destructeur
	Vector2();
	Vector2(const float, const float);
	Vector2(const Vector2&);
	~Vector2(void);

	// Accesseurs et mutateurs
	float getX() const;
	float getY() const;
	void setX(const float);
	void setY(const float);

	// Surcharge opérateur
	Vector2 operator + (const Vector2&) const;
	Vector2 operator + (const float) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator - (const float) const;
	Vector2 operator * (const Vector2&) const;
	Vector2 operator * (const float) const;
	Vector2 operator / (const Vector2&) const;
	Vector2 operator / (const float) const;
	Vector2& operator += (const Vector2&);
	Vector2& operator += (const float);
	Vector2& operator -= (const Vector2&);
	Vector2& operator -= (const float);
	Vector2& operator *= (const Vector2&);
	Vector2& operator *= (const float);
	Vector2& operator /= (const Vector2&);
	Vector2& operator /= (const float);
	Vector2& operator = (const Vector2&);
	bool operator == (const Vector2&) const;
	bool operator != (const Vector2&) const;
	bool operator < (const Vector2&) const;
	bool operator > (const Vector2&) const;

	// Autres méthodes
	float length() const;
	float squaredLength() const;
	float distance(const Vector2&) const;
	float squaredDistance(const Vector2&) const;
	float dotProduct(const Vector2&) const;
	float crossProduct(const Vector2&) const;
	float normalise();
	float angleBetween(const Vector2& v) const;
	float angleOrientedBetween(const Vector2& v) const;
	float orientationTriangle(const Vector2& v) const;
	Vector2 midPoint(const Vector2&) const;
	Vector2 normal() const;

	// Méthode d'affichage (notamment pour le debug)
	friend std::ostream& operator << (std::ostream&, const Vector2&);

	// Constantes statiques 
	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 NEGATIVE_UNIT_X;
	static const Vector2 NEGATIVE_UNIT_Y;
	static const Vector2 UNIT_SCALE;

private:
	float mX;
	float mY;
};

#endif