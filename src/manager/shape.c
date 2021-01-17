#include "shape.h"
#include <stdlib.h>

#define COLOR_BASE RED

//------------------------------------------------------------------------------------
// Private methods declaration.
//------------------------------------------------------------------------------------
void   *loadShape(ShapeType_t type);
Line_t *loadLineShape(void);

//------------------------------------------------------------------------------------
// Public methods implementation.
//------------------------------------------------------------------------------------
Shape_t initShape(ShapeType_t type) {
    Shape_t shape = (Shape_t){0};
    shape.type = type;
    shape.ptr = loadShape(type);
    return shape;
}
void freeShape(Shape_t *ptrShape) {
    if (ptrShape->ptr) {
        free(ptrShape->ptr);
        ptrShape->ptr = NULL;
    }
}

//------------------------------------------------------------------------------------
// Private methods implementation.
//------------------------------------------------------------------------------------
void *loadShape(ShapeType_t type) {
    switch (type) {
        case SHAPE_LINE:
            return loadLineShape();
        default:
            return NULL;
    }
}
Line_t *loadLineShape(void) {
    Line_t *line = malloc(sizeof(Line_t));
    line->ptoA = (Vector2){0};
    line->ptoB = (Vector2){0};
    line->color = COLOR_BASE;
    line->mod = 20;
    return line;
}
