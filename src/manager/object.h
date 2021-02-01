#ifndef RC_OBJECT_H
#define RC_OBJECT_H

#define NUM_OBJECTS 2

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ObjectType_t {
    OBJ_MAP = 0,
    OBJ_PLAYER
} ObjectType_t;

typedef struct Object_t {
    ObjectType_t type;
    void *obj;
} Object_t;

Object_t storeObject[NUM_OBJECTS];

void initStoreObject(void);
void updateAllObject(void (*funcPtr)(Object_t *const));
void drawAllObject(void (*funcPtr)(const Object_t *const));
void freeStoreObject(void);

#ifdef __cplusplus
}
#endif
#endif //RC_OBJECT_H
