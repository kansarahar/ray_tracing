#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>

using namespace std;

#pragma pack(push, 1)

struct BitmapFileHeader {
    uint16_t bf_type = 19778;
    uint32_t bf_size = 0;           //sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + biWidth*biHeight*3
    uint16_t bf_reserved1 = 0;
    uint16_t bf_reserved2 = 0;
    uint32_t bf_offset_bits = 54;
};

struct BitmapInfoHeader {
    uint32_t bi_size = 40;
    uint32_t bi_width = 4;
    uint32_t bi_height = 4;
    uint16_t bi_planes = 1;
    uint16_t bi_bit_count = 24;
    uint32_t bi_compression = 0;
    uint32_t bi_size_image = 0;
    uint32_t bi_x_px_per_meter = 0;
    uint32_t bi_y_px_per_meter = 0;
    uint32_t bi_clr_used = 0;
    uint32_t bi_clr_important = 0;
};

#pragma pack(pop)




#endif