#include "Color.h"

Color::Color()
{
	mRed = 0.0f;
	mGreen = 0.0f;
	mBlue = 0.0f;
	mAlpha = 1.0f;
}

Color::Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f) : mRed(r), mGreen(g), mBlue(b), mAlpha(a)
{

}

Color::Color(const Color& c) : mRed(c.mRed), mGreen(c.mGreen), mBlue(c.mBlue), mAlpha(c.mAlpha)
{

}

Color::~Color()
{
}

void Color::setRed(float r)
{ 
	mRed = r;
}

float Color::getRed() const
{
	return mRed;
}

void Color::setGreen(float g)
{
	mGreen = g;
}

float Color::getGreen() const
{
	return mGreen;
}

void Color::setBlue(float b)
{
	mBlue = b;
}

float Color::getBlue() const
{
	return mBlue;
}

void Color::setAlpha(float a)
{
	mAlpha = a;
}

float Color::getAlpha() const
{
	return mAlpha;
}

float Color::greyLevel() const
{
	return (mRed + mGreen + mBlue) / 3.0f;
}
