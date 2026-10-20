#ifndef CRX_DECODER_H
#define CRX_DECODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Decode one CRX sample (Canon CR3 raw codec: tile/plane/subband headers +
 * plane bitstreams) as stored in MLV frames with MLV_VIDEO_CLASS_FLAG_CRX,
 * recorded by mlv_lite on DIGIC 8, into width x height 16-bit Bayer values.
 * Tiles (side by side, equal width) are counted from the sample's headers.
 * cfa_layout: plane-to-Bayer order (0 RGGB, 1 GRBG, 2 GBRG, 3 BGGR);
 * enc_type: 0 plain planes, 3 decorrelated planes.  mlv_lite's own encodes
 * (Canon's reduced-raw setup) use 1 / 0; frames from Canon's full-raw setup
 * (MLV_VIDEO_CLASS_FLAG_CRX_FULL, RAW burst pre-shooting) 0 / 3.
 * levels: wavelet levels, 0 = lossless, 3 = C-RAW; -1 = from the sample's
 * subband headers.  Returns 0 on success. */
int crx_decode_frame(const uint8_t *data, uint32_t size,
                     int width, int height, int bits,
                     int cfa_layout, int enc_type, int levels, uint16_t *out);

#ifdef __cplusplus
}
#endif

#endif
