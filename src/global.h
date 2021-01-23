#ifndef RC_GLOBAL_H
#define RC_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

float   lengthVectorGlobal(Vector2 v);
Vector2 normalizedVectorGlobal(Vector2 v);
void    printVectorGlobal(Vector2 v);
Vector2 addVectorGlobal(Vector2 v1, Vector2 v2);
Vector2 multVectorGlobal(Vector2 v, float value);
float   getAngleGlobal(float angle, float value);
Vector2 getSmallVector(const Vector2 v1, const Vector2 v2);
Vector2 getUnitVectorToAngle(const float angle);
bool isLookUp(const float angle);
bool isLookLeft(const float angle);
#endif //RC_GLOBAL_H
