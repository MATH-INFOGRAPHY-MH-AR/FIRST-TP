#ifndef COLOR_H
#define COLOR_H


class Color
{
private:
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;

public:
	Color();
	Color(float, float, float, float);
	Color(const Color&);
	~Color();

	void setRed(float);
	float getRed() const;

	void setGreen(float);
	float getGreen() const;

	void setBlue(float);
	float getBlue() const;

	void setAlpha(float);
	float getAlpha() const;

	float greyLevel() const;
};

#endif