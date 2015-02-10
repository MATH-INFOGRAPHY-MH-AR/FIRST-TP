#ifndef MAILLON_H 
#define MAILLON_H

#include "Vector2.h"

typedef struct s_LCAStruct
{
	float xmin;
	float ymin;

	float xmax;
	float ymax;
	
	float coeffInversed;

} LCAStruct;

bool compareXMin(const LCAStruct lca_1, const LCAStruct lca_2);

typedef struct s_Line
{
	Vector2 start;
	Vector2 end;

} Line;

#endif