#include <raylib.h>
#include "src/system/render.h"
#include "src/manager/object.h"

int main(void) {
    initRender();
    initStoreObject();
    while (!WindowShouldClose()) {
        updateRender();
    }
    freeStoreObject();
    CloseWindow();
    return 0;
}