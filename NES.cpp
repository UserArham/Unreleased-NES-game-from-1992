#include <stdint.h>
#include <string.h>
#include <emscripten.h>

static uint8_t framebuffer[256 * 240 * 4];

extern "C" {

EMSCRIPTEN_KEEPALIVE
void nes_init() {
    memset(framebuffer, 0, sizeof(framebuffer));
}

EMSCRIPTEN_KEEPALIVE
void nes_reset() {
    nes_init();
}

EMSCRIPTEN_KEEPALIVE
void nes_step() {
    // Fake PPU output for now (placeholder)
    // Replace with real CPU + PPU logic later
    static int t = 0;
    t++;

    for (int y = 0; y < 240; y++) {
        for (int x = 0; x < 256; x++) {
            int i = (y * 256 + x) * 4;
            framebuffer[i + 0] = (x + t) & 255; // R
            framebuffer[i + 1] = (y + t) & 255; // G
            framebuffer[i + 2] = 128;           // B
            framebuffer[i + 3] = 255;           // A
        }
    }
}

EMSCRIPTEN_KEEPALIVE
uint8_t* nes_framebuffer() {
    return framebuffer;
}

}
