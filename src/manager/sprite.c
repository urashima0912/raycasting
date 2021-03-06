#include "sprite.h"
#include <stdlib.h>

//TODO: changed init function.
Sprite_t *initSprite(void) {
    Sprite_t *sprite = malloc(sizeof(Sprite_t));
    sprite->texture = LoadTexture("assets/sprites/male.png");
    sprite->position = (Vector2){100, 70};
    sprite->angle = 0;
    sprite->length = 0;
    sprite->size = (Vector2i_t){64, 64};
    sprite->visible = false;
    return sprite;
}
void freeSprite(Sprite_t **ptrSprite) {
    if ((*ptrSprite)) {
        UnloadTexture((*ptrSprite)->texture);
        free((*ptrSprite));
        (*ptrSprite) = NULL;
    }
}