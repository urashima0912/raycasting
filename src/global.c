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
    const float max = 2 * PI;
    float newAngle = fmod((angle + value), max);
    if (newAngle < 0)
        newAngle += max;
    return newAngle;
}
Vector2 getSmallVector(const Vector2 v1, const Vector2 v2) {
    const float lenV1 = lengthVectorGlobal(v1);
    const float lenV2 = lengthVectorGlobal(v2);

    if (lenV1 < lenV2) return v1;
    else return v2;
}
Vector2 getUnitVectorToAngle(const float angle) {
    Vector2 unit = (Vector2){0};
    unit.x = cos(angle);
    unit.y = sin(angle);
    return unit;
}
bool isLookUp(const float angle) {
    if (angle > PI && angle < 2 * PI)
        return true;
    return false;
}
bool isLookLeft(const float angle) {
    if (angle > PI/2 && angle < 3*PI/2)
        return true;
    return false;
}

