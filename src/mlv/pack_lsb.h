/*
 * Unpacking for MLV_VIDEO_CLASS_FLAG_PACK_LSB frames.
 *
 * DIGIC 8 cameras (EOS M6 Mark II) write raw frames as a plain bit stream
 * read LSB first from bytes: pixel i occupies bits [i*bpp, i*bpp+bpp) of the
 * frame, bit 0 being the lowest bit of byte 0 (12-bit: 3 bytes -> 2 pixels,
 * p0 = b0 | (b1 & 0xF) << 8, p1 = b1 >> 4 | b2 << 4). ML's usual layout is an
 * MSB-first stream in 16-bit little endian words instead.
 */

#ifndef _pack_lsb_h_
#define _pack_lsb_h_

#include <stdint.h>

/* unpack a PACK_LSB frame to 16 bit, like dng_unpack_image_bits does for ML's
   layout. input_buffer needs 4 bytes of slack after the frame. */
static inline void unpack_lsb_image_bits(uint16_t * output_buffer, const uint8_t * input_buffer, int width, int height, uint32_t bpp)
{
    uint32_t pixel_count = width * height;
    uint32_t mask = (1 << bpp) - 1;

    #pragma omp parallel for
    for (uint32_t pixel_index = 0; pixel_index < pixel_count; pixel_index++)
    {
        uint32_t bits_offset = pixel_index * bpp;
        const uint8_t * p = input_buffer + bits_offset / 8;
        /* bpp <= 16 plus a shift of up to 7 fits in 3 bytes */
        uint32_t data = p[0] | (p[1] << 8) | (p[2] << 16);
        output_buffer[pixel_index] = (uint16_t)((data >> (bits_offset % 8)) & mask);
    }
}

#endif
