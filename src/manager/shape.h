#ifndef RC_SHAPE_H
#define RC_SHAPE_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ShapeType_t {
    SHAPE_LINE = 0
} ShapeType_t;

typedef struct Line_t {
    Vector2 ptoA;
    Vector2 ptoB;
    float mod;
    Color color;
} Line_t;

typedef struct Shape_t {
    ShapeType_t type;
    void *ptr;
} Shape_t;

Shape_t initShape(ShapeType_t type);
void freeShape(Shape_t *ptrShape);

#ifdef __cplusplus
}
#endif
#endif //RC_SHAPE_H
