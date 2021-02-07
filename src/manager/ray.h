#ifndef RC_RAY_H
#define RC_RAY_H

#include <raylib.h>
#include <stdint.h>

#define RAY_COLOR_BASE  RAYWHITE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Ray_t {
    Vector2 ptoA;
    Vector2 ptoB;
    float angle;
    float length;
    float pixelPos;
    Color color;
    uint32_t wallType;
} Ray_t;

#ifdef __cplusplus
}
#endif
#endif //RC_RAY_H
