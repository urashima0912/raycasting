#ifndef RC_OBJECT_H
#define RC_OBJECT_H

#define NUM_OBJECTS 1

typedef enum ObjectType_t{
    OBJ_MAP = 0
}ObjectType_t;

typedef struct Object_t {
    ObjectType_t type;
    void *obj;
}Object_t;

Object_t storeObject[NUM_OBJECTS];

void initStoreObject(void);
void drawAllObject(void (*funcPrt)(const Object_t *const));
void freeStoreObject(void);

#endif //RC_OBJECT_H
