#include "Constants.h"

std::vector<Polygon*> polygons;
std::vector<Polygon*> windows;
std::vector<Polygon*> outputPolygons;

bool MIDDLE_BUTTON_PRESSED = false;
bool SHOW_HIDE_OUTPUT_POLYGONS = true;

int WINDOW_OR_POLYGON_EDITED = -1;
int CURRENT_POLYGON_EDITED = -1;
int CURRENT_VERTEX_EDITED = 0;
