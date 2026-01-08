#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

static uint8_t framebuffer[256*240*4];
static uint8_t* prg_rom = nullptr;
static uint8_t* chr_rom = nullptr;
static int prg_size = 0;
static int chr_size = 0;
static uint8_t palette[32]; // 16 bg + 16 sprite

extern "C" {

// Initialize NES
EMSCRIPTEN_KEEPALIVE
void nes_init() {
    memset(framebuffer, 0, sizeof(framebuffer));
    memset(palette, 0x0F, sizeof(palette)); // default
}

// Reset NES
EMSCRIPTEN_KEEPALIVE
void nes_reset() {
    nes_init();
}

// NES step (render framebuffer placeholder)
EMSCRIPTEN_KEEPALIVE
void nes_step() {
    static int t=0; t++;
    for(int y=0;y<240;y++){
        for(int x=0;x<256;x++){
            int i=(y*256+x)*4;
            framebuffer[i+0] = (x+t) & 0xFF; // R
            framebuffer[i+1] = (y+t) & 0xFF; // G
            framebuffer[i+2] = palette[(x+y)%16]; // B (demo)
            framebuffer[i+3] = 255;
        }
    }
}

// Return framebuffer pointer
EMSCRIPTEN_KEEPALIVE
uint8_t* nes_framebuffer() {
    return framebuffer;
}

// Load NES ROM
EMSCRIPTEN_KEEPALIVE
void nes_load_rom(uint8_t* data, int size) {
    if(size<16) return;
    if(data[0]!='N'||data[1]!='E'||data[2]!='S') return; // iNES
    prg_size = data[4]*16384;
    chr_size = data[5]*8192;
    int offset = 16;
    if(prg_rom) free(prg_rom);
    prg_rom = (uint8_t*)malloc(prg_size);
    memcpy(prg_rom, data+offset, prg_size);
    offset+=prg_size;
    if(chr_size>0){
        if(chr_rom) free(chr_rom);
        chr_rom = (uint8_t*)malloc(chr_size);
        memcpy(chr_rom, data+offset, chr_size);
    }
}

// Load NES Palette
EMSCRIPTEN_KEEPALIVE
void nes_load_palette(uint8_t* data, int size){
    if(size!=32) return;
    memcpy(palette, data, 32);
}

}
