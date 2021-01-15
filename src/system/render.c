#include "render.h"
#include "../../config.h"
#include <raylib.h>

void initRender(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(SCREEN_FPS);
}

void updateRender(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}
