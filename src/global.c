#include "global.h"
#include <raymath.h>

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
float lengthVectorGlobal(Vector2 v) {
    const float value = pow(v.x, 2) + pow(v.y, 2);
    return sqrt(value);
}
Vector2 normalizedVectorGlobal(Vector2 v) {
    Vector2 unit = (Vector2){0};
    const float mod = lengthVectorGlobal(v);
    unit.x = v.x / mod;
    unit.y = v.y / mod;
    return unit;
}
void printVectorGlobal(Vector2 v) {
    TraceLog(LOG_INFO, "(x: %f, y: %f)", v.x, v.y);
}
Vector2 addVectorGlobal(Vector2 v1, Vector2 v2) {
    return (Vector2){ v1.x + v2.x, v1.y + v2.y};
}
Vector2 multVectorGlobal(Vector2 v, float scalar) {
    return (Vector2){ v.x * scalar, v.y * scalar};
}
float getAngleGlobal(float angle, float value) {
    float newAngle = angle + value;
    if (newAngle > 360)
        newAngle = 0;
    else if (newAngle < 0)
        newAngle = 360;
    return newAngle;
}

