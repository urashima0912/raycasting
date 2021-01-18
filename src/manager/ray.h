#ifndef RC_RAY_H
#define RC_RAY_H

#include <raylib.h>

#define COLOR_BASE RAYWHITE

typedef struct Ray_t {
    Vector2 ptoA;
    Vector2 ptoB;
    float   angle;
}Ray_t;

#endif //RC_RAY_H
