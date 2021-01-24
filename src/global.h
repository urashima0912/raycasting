#ifndef RC_GLOBAL_H
#define RC_GLOBAL_H

#include <raylib.h>
#include <stdint.h>

typedef struct gConfig_t {
    // window data.
    int32_t screeWidth;
    int32_t screeHeight;
    const char *screenTitle;
    // canvas data.
    int32_t canvasWidth;
    int32_t canvasHeight;
    int32_t canvasTileWidth;
    int32_t canvasTileHeight;
    int32_t canvasNumRays;
}gConfig_t;

gConfig_t globalConfig;

void        initGlobalConfig(void);
void        printVectorGlobal(Vector2 v);
float       lengthVectorGlobal(Vector2 v);
float       getAngleGlobal(float angle, float value);
float       getSmallLengthV(const Vector2 v1, const Vector2 v2);
bool        isLookUp(const float angle);
bool        isPositionInsideMap(const Vector2 v);
bool        isLookLeft(const float angle);
bool        areEqualV(const Vector2 v1, const Vector2 v2);
Vector2     normalizedVectorGlobal(Vector2 v);
Vector2     addVectorGlobal(Vector2 v1, Vector2 v2);
Vector2     multVectorGlobal(Vector2 v, float value);
Vector2     getSmallVector(const Vector2 v1, const Vector2 v2);
Vector2     getUnitVectorToAngle(const float angle);

#endif //RC_GLOBAL_H
