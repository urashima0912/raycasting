#include "object.h"
#include "map.h"

void initStoreObject(void) {
    storeObject[0].type = OBJ_MAP;
    storeObject[0].obj = (Map_t *)initMap(LEVEL_0);
}

void drawAllObject(void (*funcPrt)(const Object_t *const)) {
    funcPrt(storeObject);
}

void freeStoreObject(void) {
    freeMap((Map_t **)&storeObject[0].obj);
}