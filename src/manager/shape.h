#ifndef RC_SHAPE_H
#define RC_SHAPE_H

#include <raylib.h>

typedef struct Line_t {
    Vector2 ptoA;
    Vector2 ptoB;
    Color   color;
}Line_t;

Line_t initLineShape(Vector2 ptoA, Vector2 ptoB, Color color);

#endif //RC_SHAPE_H
