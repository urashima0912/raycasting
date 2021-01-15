#include <raylib.h>
#include "src/system/render.h"

int main(void) {
    initRender();
    while (!WindowShouldClose()) {
        updateRender();
    }
    CloseWindow();
    return 0;
}