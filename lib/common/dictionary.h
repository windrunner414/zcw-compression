#ifndef LIBZCW_DICTIONARY_H
#define LIBZCW_DICTIONARY_H

namespace zcw {
    const uint16_t kOneByteCodeNum = 191U; // [1, 191]
    const uint16_t kTwoByteCodeNum = 0x3FFFU + 1; // [192, 16575]

    static inline uint8_t is_little_endian() {
        int x = 1;
        return *reinterpret_cast<uint8_t *>(&x);
    }

    static inline uint16_t bswap_16(uint16_t x) {
        return static_cast<uint16_t>(x >> 8U) | static_cast<uint16_t>(x << 8U);
    }
}

#endif //LIBZCW_DICTIONARY_H
