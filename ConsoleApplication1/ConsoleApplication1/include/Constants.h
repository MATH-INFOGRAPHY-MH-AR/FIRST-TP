#ifndef CONSTANT_H
#define CONSTANT_H

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

#include "Polygon.h"

extern std::vector<Polygon*> polygons;
extern std::vector<Polygon*> windows;
extern std::vector<Polygon*> outputPolygons;

extern bool MIDDLE_BUTTON_PRESSED;
extern bool SHOW_HIDE_OUTPUT_POLYGONS;
extern bool CURRENT_STEP_BY_STEP_CHOSEN;

extern int WINDOW_OR_POLYGON_EDITED;
extern int CURRENT_POLYGON_EDITED;
extern int CURRENT_VERTEX_EDITED;
extern int CURRENT_LCA_SHOWN;

#endif