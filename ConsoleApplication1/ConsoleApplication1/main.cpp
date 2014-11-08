#include "Vector2.h"
#include "Polygon.h"


int main(void)
{
	Vector2 A(1.0f, 5.0f);
	Vector2 B(4.0f, 3.0f);
	Vector2 C(3.0f, 6.0f);
	Vector2 D(4.0f, 7.0f);
	
	std::cout << coupe(A, B, C, D) << std::endl;

	return 0;
}