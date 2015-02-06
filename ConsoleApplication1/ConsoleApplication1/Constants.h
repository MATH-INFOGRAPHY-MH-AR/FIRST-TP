#ifndef CONSTANT_H
#define CONSTANT_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#include "Polygon.h"

extern std::vector<Polygon*> polygons;
extern std::vector<Polygon*> windows;
extern Vector2 VECTOR_EDITED;

extern int WINDOW_OR_POLYGON_EDITED;
extern int CURRENT_POLYGON_EDITED;

extern int state;

#endif