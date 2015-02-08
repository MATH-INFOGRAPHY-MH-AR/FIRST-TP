#include "Constants.h"

std::vector<Polygon*> polygons;
std::vector<Polygon*> windows;

bool MIDDLE_BUTTON_PRESSED = false;
int WINDOW_OR_POLYGON_EDITED = -1;
int CURRENT_POLYGON_EDITED = -1;
int CURRENT_VERTEX_EDITED = 0;

int state;