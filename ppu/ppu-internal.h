#ifndef PPU_INTERNAL_H
#define PPU_INTERNAL_H

#include <stdint.h>

#define MCYCLES_PER_LINE 114
#define MCYCLES_OAM_SCAN_MODE 20
#define MCYCLES_DRAWING_MODE 43
#define MCYCLES_HBLANK_MODE 51
#define MCYCLES_VBLANK_MODE 114

enum ppu_mode
{
    hblank_mode,   /*mode0*/
    vblank_mode,   /*mode1*/
    oam_scan_mode, /*mode2*/
    drawing_mode,  /*mode3*/
};

struct PPU
{
    uint8_t *vram;
    uint8_t *oam;
    enum ppu_mode mode;
    uint16_t mcycles;

    struct
    {
        union
        {
            uint8_t val;
            struct
            {
                uint8_t bg_win_enable : 1;
                uint8_t obj_enable : 1;
                uint8_t obj_size : 1;
                uint8_t bg_tile_map : 1;
                uint8_t bg_win_tiles : 1;
                uint8_t win_enable : 1;
                uint8_t win_tile_map : 1;
                uint8_t ppu_enable : 1;
            };
        } control; /*0xFF40*/

        struct
        {
            union
            {
                uint8_t val;
                struct
                {
                    uint8_t ppu_mode : 2;
                    uint8_t ly_eq_lyc : 1;
                    uint8_t hblank_int : 1;
                    uint8_t vblank_int : 1;
                    uint8_t oam_scan_int : 1;
                    uint8_t lyc_int : 1;
                };
            } stat;      /*0xFF41*/
            uint8_t ly;  /*0xFF44, read-only*/
            uint8_t lyc; /*0xFF45*/
        } status;
    } lcd;

    struct
    {
        uint8_t scy; /*0xFF42*/
        uint8_t scx; /*0xFF43*/
        uint8_t wy;  /*0xFF4A*/
        uint8_t wx;  /*0xFF4B*/
    } scrolling;

    struct
    {
        uint8_t bgp;  /*0xFF47*/
        uint8_t obp0; /*0xFF48*/
        uint8_t obp1; /*0xFF49*/
    } pallete;
};

extern struct PPU ppu;

void render_update_scanline(uint8_t ly);
void render_update_screen();

#endif