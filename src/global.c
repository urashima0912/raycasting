#include "global.h"
#include <raymath.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------
// Private functions declaration.
//------------------------------------------------------------------------------------
static void     quicksort(int32_t *array, int32_t low, int32_t high);
static int32_t  getMiddleIndex(int32_t *array, int32_t low, int32_t high);
static void     swap(int32_t *a, int32_t *b);


//------------------------------------------------------------------------------------
// Public functions implementation.
//------------------------------------------------------------------------------------
void initGlobalConfig(void) {
    globalConfig.screeWidth = 640;
    globalConfig.screeHeight = 480;
    globalConfig.screenTitle = "Dungeon alpha";
    globalConfig.canvasTileWidth = 32;
    globalConfig.canvasTileHeight = 32;

//    globalConfig.canvasWidth = L0_COLUMN * globalConfig.canvasTileWidth;
//    globalConfig.canvasHeight = L0_ROW * globalConfig.canvasTileHeight;

    globalConfig.canvasWidth = 640;
    globalConfig.canvasHeight = 480;

    globalConfig.canvasNumRays = globalConfig.canvasWidth;
    globalConfig.FOV = 60.0f;
    globalConfig.middleFOV = globalConfig.FOV / 2.0f;

    globalConfig.viewMap = false;
    globalConfig.viewFPS = true; //TODO: default false.
    // init camera data.
    globalCamera = (Camera2D){0};
    globalCamera.target = (Vector2){0};
    globalCamera.zoom = 1.0f;
    globalCamera.rotation = 0.0f;
    globalCamera.offset = (Vector2){
        globalConfig.canvasWidth/2,
        globalConfig.canvasHeight/2
    };

    globalConfig.playerAngle = NULL;
    globalConfig.playerPosition = NULL;
}
void initGlobalZBuffer(void) {
    const int32_t nRays = globalConfig.canvasWidth;
    globalZBuffer = malloc(sizeof(float *) * nRays);
}
void freeGlobalZBuffer(void) {
    if (globalZBuffer) {
        free(globalZBuffer);
        globalZBuffer = NULL;
    }
}
void sortArrayGlobal(int32_t *array, int32_t size) {
    quicksort(array, 0, size);
}
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
    float newAngle = fmodf((angle + value), max);
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
float getSmallLengthV(const Vector2 v1, const Vector2 v2) {
    const float lenV1 = lengthVectorGlobal(v1);
    const float lenV2 = lengthVectorGlobal(v2);

    if (lenV1 < lenV2) return lenV1;
    else return lenV2;
}
bool areEqualV(const Vector2 v1, const Vector2 v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
//------------------------------------------------------------------------------------
// Private functions implementation.
//------------------------------------------------------------------------------------
static void swap(int32_t *a, int32_t *b) {
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}
static void quicksort(int32_t *array, int32_t low, int32_t high) {
    if (low < high) {
        int32_t index = getMiddleIndex(array, low, high);
        quicksort(array, low, index - 1);
        quicksort(array, index + 1, high);
    }
}
static int32_t getMiddleIndex(int32_t *array, int32_t low, int32_t high) {
    int32_t pivot = array[high];
    int32_t index = low - 1;

    for (int32_t k=low; k < (high - 1); ++k) {
        if (array[k] < pivot) {
            ++index;
            swap(&array[index], &array[k]);
        }
    }
    swap(&array[index + 1], &array[high]);
    return (index + 1);
}
bool loadGlobalResources(void) {
    globalConfig.wallsTextures = LoadTexture("assets/sprites/walls.png");
    globalConfig.floorsTextures = LoadTexture("assets/sprites/floors.png");
    return true;
}
void freeGlobalResources(void) {
    UnloadTexture(globalConfig.wallsTextures);
    UnloadTexture(globalConfig.floorsTextures);
}