#include <raylib.h>
#include "config.h"
#include "src/system/render.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(SCREEN_FPS);

    while (!WindowShouldClose()) {
        updateRender();
    }
    CloseWindow();
    return 0;
}