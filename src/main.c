#include "neslib.h"
#include "kirby.h"

void main(void) {
    ppu_off();

    pal_bg(palette_bg);
    pal_spr(palette_sp);

    vram_adr(NAMETABLE_A);
    vram_fill(0x00, 1024);

    kirby_init();

    ppu_on_all();

    while (1) {
        ppu_wait_nmi();
        pad_poll(0);
        kirby_update();
    }
}
