#include "global.h"
#include <raymath.h>

//------------------------------------------------------------------------------------
// Public method implementation.
//------------------------------------------------------------------------------------
float lengthVectorGlobal(Vector2 vector) {
    const float value = pow(vector.x, 2) + pow(vector.y, 2);
    return sqrt(value);
}
Vector2 normalizedVectorGlobal(Vector2 vector) {
    Vector2 unit = (Vector2){0};
    const float mod = lengthVectorGlobal(vector);
    unit.x = vector.x / mod;
    unit.y = vector.y / mod;
    return unit;
}
