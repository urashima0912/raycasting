#include "sprite.h"
#include <stdlib.h>

//TODO: changed init function.
Sprite_t *initSprite(void) {
    Sprite_t *sprite = malloc(sizeof(Sprite_t));
    sprite->texture = LoadTexture("assets/sprites/male.png");
    sprite->position = (Vector2){350, 100};
    sprite->angle = 0;
    sprite->length = 0;
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