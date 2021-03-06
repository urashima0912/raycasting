#ifndef RC_SPRITE_H
#define RC_SPRITE_H

#include <raylib.h>
#include "../global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Sprite_t {
    Texture texture;
    Vector2 position;
    Vector2i_t size;
    float angle;
    float length;
    bool visible;
} Sprite_t;

Sprite_t *initSprite(void);
void freeSprite(Sprite_t **ptrSprite);

#ifdef __cplusplus
}
#endif
#endif //RC_SPRITE_H
