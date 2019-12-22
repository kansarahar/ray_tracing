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

void save_bmp(uint32_t width_px, uint32_t height_px, double*** image_arr) {
    BitmapFileHeader bfh;
    BitmapInfoHeader bih;

    bih.bi_width = width_px;
    bih.bi_height = height_px;

    FILE *file = fopen("image.bmp", "wb");
    if (!file) {
        printf("Could not write file\n");
        return;
    }

    /*Write headers*/
    fwrite(&bfh, 1, sizeof(bfh), file);
    fwrite(&bih, 1, sizeof(bih), file);

    /*Write bitmap*/
    for (int y = bih.bi_height-1; y>=0; y--) { /*Scanline loop backwards*/
        for (int x = 0; x < bih.bi_width; x++) { /*Column loop forwards*/
            /*compute some pixel values*/
            unsigned char r = image_arr[y][x][0];
            unsigned char g = image_arr[y][x][1];
            unsigned char b = image_arr[y][x][2];
            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
        int bytes_in_row = bih.bi_width*bih.bi_bit_count/8;
        if (bytes_in_row%4 > 0) {
            for (int i = 0; i < 4-bytes_in_row%4; i++) {
                unsigned char zero = 0;
                fwrite(&zero, 1, 1, file);
            }
        }
    }
    fclose(file);
    return;
}


#endif