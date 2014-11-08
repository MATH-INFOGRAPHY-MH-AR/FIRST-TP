/*
Fichier :							Vector2
Date de création :					05/11/2014
Date de dernière modification :		06/11/2014
Auteur:								Alexandre Rivet
*/

#include <cmath>
#include "Vector2.h"
//#include "MathFunc.h"
#define PI 3.14159f

float radianToDegree(float rad);
float degreeToRadian(float deg);

Vector2::Vector2()
{
	mX = 0;
	mY = 0;
}

Vector2::Vector2(const float x, const float y)
{
	mX = x;
	mY = y;
}

Vector2::Vector2(const Vector2& v)
{
	mX = v.mX;
	mY = v.mY;
}

Vector2::~Vector2(void) {}

float Vector2::getX() const
{
	return mX;
}

float Vector2::getY() const
{
	return mY;
}

void Vector2::setX(const float x)
{
	mX = x;
}

void Vector2::setY(const float y)
{
	mY = y;
}

Vector2 Vector2::operator + (const Vector2& v) const
{
	return Vector2(
		mX + v.mX,
		mY + v.mY);
}

Vector2 Vector2::operator + (const float s) const
{
	return Vector2(
		mY + s,
		mY + s);
}

Vector2 Vector2::operator - (const Vector2& v) const
{
	return Vector2(
		mX - v.mX,
		mY - v.mY);
}

Vector2 Vector2::operator - (const float s) const
{
	return Vector2(
		mX - s,
		mY - s);
}

Vector2 Vector2::operator * (const Vector2& v) const
{
	return Vector2(
		mX * v.mX,
		mY * v.mY);
}

Vector2 Vector2::operator * (const float s) const
{
	return Vector2(
		mX * s,
		mY * s);
}

Vector2 Vector2::operator / (const Vector2& v) const
{
	if (v.mX == 0 && v.mY == 0) return Vector2::ZERO;
	return Vector2(
		mX / v.mX,
		mY / v.mY);
}

Vector2 Vector2::operator / (const float s) const
{
	if (s == 0) return Vector2::ZERO;
	return Vector2(
		mX / s,
		mY / s);
}

Vector2& Vector2::operator += (const Vector2& v)
{
	mX += v.mX;
	mY += v.mY;
	return *this;
}

Vector2& Vector2::operator += (const float s)
{
	mX += s;
	mY += s;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& v)
{
	mX -= v.mX;
	mY -= v.mY;
	return *this;
}

Vector2& Vector2::operator -= (const float s)
{
	mX -= s;
	mY -= s;
	return *this;
}

Vector2& Vector2::operator *= (const Vector2& v)
{
	mX *= v.mX;
	mY *= v.mY;
	return *this;
}

Vector2& Vector2::operator *= (const float s)
{
	mX *= s;
	mY *= s;
	return *this;
}

Vector2& Vector2::operator /= (const Vector2& v)
{
	if (v.mX == 0 && v.mY == 0) return *this;
	mX /= v.mX;
	mY /= v.mY;
	return *this;
}

Vector2& Vector2::operator /= (const float s)
{
	if (s == 0) return *this;
	mX /= s;
	mY /= s;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& v)
{
	mX = v.mX;
	mY = v.mY;
	return *this;
}

bool Vector2::operator == (const Vector2& v) const
{
	return ((mX == v.mX) && (mY == v.mY));
}

bool Vector2::operator != (const Vector2& v)const
{
	return ((mX != v.mX) || (mY != v.mY));
}

bool Vector2::operator < (const Vector2& v) const
{
	return ((mX < v.mX) && (mY < v.mY));
}

bool Vector2::operator >(const Vector2& v) const
{
	return ((mX > v.mX) && (mY > v.mY));
}

std::ostream& operator << (std::ostream& os, const Vector2& v)
{
	os << "Vector2(" << v.mX << "," << v.mY << ")";
	return os;
}

float Vector2::length() const
{
	return sqrt(mX * mX + mY * mY);
}

float Vector2::squaredLength() const
{
	return mX * mX + mY * mY;
}

float Vector2::distance(const Vector2& v) const
{
	return (*this - v).length();
}

float Vector2::squaredDistance(const Vector2& v) const
{
	return (*this - v).squaredLength();
}

float Vector2::dotProduct(const Vector2& v) const
{
	return mX * v.mX + mY * v.mY;
}

float Vector2::crossProduct(const Vector2& v) const
{
	return mX * v.mY - v.mX * mY;
}

float Vector2::normalise()
{
	float len = length();

	if (len > 0.0f)
	{
		mX /= len;
		mY /= len;
	}
	return len;
}

float Vector2::angleBetween(const Vector2& v) const
{
	float lenProduct = length() * v.length();
	return radianToDegree(acos(dotProduct(v) / lenProduct));
}

float Vector2::angleOrientedBetween(const Vector2& v) const
{
	float orientation = orientationTriangle(v);
	if (orientation < 0)
		return 360.0f - angleBetween(v);
	else if (orientation > 0)
		return radianToDegree(angleBetween(v));
	else
		return 0.0f;
}

float Vector2::orientationTriangle(const Vector2& v) const
{
	if (crossProduct(v) > 0)
		return 1;
	else if (crossProduct(v) < 0)
		return -1;
	else return 0;
}

Vector2 Vector2::midPoint(const Vector2& v) const
{
	return Vector2(
		(mX + v.mX) * 0.5f,
		(mY + v.mY) * 0.5f);
}

Vector2 Vector2::normal() const
{
	return Vector2(-mY, mX);
}

const Vector2 Vector2::ZERO(0, 0);
const Vector2 Vector2::UNIT_X(1, 0);
const Vector2 Vector2::UNIT_Y(0, 1);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1, 0);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0, -1);
const Vector2 Vector2::UNIT_SCALE(1, 1);



float radianToDegree(float rad)
{
	return 180 * rad / PI;
}

float degreeToRadian(float deg)
{
	return PI * deg / 180;
}

