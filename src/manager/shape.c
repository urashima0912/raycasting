#include "shape.h"

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Line_t initLineShape(Vector2 ptoA, Vector2 ptoB, Color color) {
    Line_t line = (Line_t){0};
    line.ptoA = ptoA;
    line.ptoB = ptoB;
    line.color = color;
    return line;
}


