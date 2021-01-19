#ifndef RC_RAY_H
#define RC_RAY_H

#include <raylib.h>

#define RAY_COLOR_BASE  RAYWHITE
#define NUM_RAYS    1

typedef struct Ray_t {
    Vector2 ptoA;
    Vector2 ptoB;
    float   angle;
    Color   color;
}Ray_t;

#endif //RC_RAY_H