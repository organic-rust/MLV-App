#ifndef CRX_DECODER_H
#define CRX_DECODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Decode one CRX sample (Canon CR3 raw codec: tile/plane/subband headers +
 * 4 plane bitstreams) of a single-tile frame, as stored in MLV frames with
 * MLV_VIDEO_CLASS_FLAG_CRX, into width x height 16-bit Bayer values.
 * cfa_layout: plane-to-Bayer order (0 RGGB, 1 GRBG, 2 GBRG, 3 BGGR);
 * mlv_lite's encoder (Canon's reduced-raw setup) uses 1.
 * levels: wavelet levels, 0 = lossless.  Returns 0 on success. */
int crx_decode_frame(const uint8_t *data, uint32_t size,
                     int width, int height, int bits,
                     int cfa_layout, int levels, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif
