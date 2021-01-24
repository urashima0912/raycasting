#ifndef RC_SPRITE_H
#define RC_SPRITE_H

#include <raylib.h>

typedef struct Sprite_t {
    Texture texture;
    Vector2 position;
    float angle;
    float length;
    bool visible;
}Sprite_t;

Sprite_t    *initSprite(void);
void        freeSprite(Sprite_t **ptrSprite);

#endif //RC_SPRITE_H
