#include "kirby.h"
#include "neslib.h"

unsigned char kx, ky;
signed char vy;
unsigned char is_floating;

void kirby_init(void) {
    kx = 120;
    ky = 100;
    vy = 0;
    is_floating = 0;
}

void kirby_update(void) {
    unsigned char pad = pad_state(0);

    if (pad & PAD_LEFT)  kx--;
    if (pad & PAD_RIGHT) kx++;

    if (pad & PAD_A) {
        is_floating = 1;
        vy = -1;
    }

    if (!is_floating) vy++;
    ky += vy;

    if (ky > 200) {
        ky = 200;
        vy = 0;
        is_floating = 0;
    }

    oam_clear();
    oam_spr(kx, ky, 0x10, 0x00, 0);
}
