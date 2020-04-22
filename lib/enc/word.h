#ifndef LIBZCW_WORD_H
#define LIBZCW_WORD_H

#include <cstdint>
#include <string_view>

#include "internal.h"

namespace zcw {
    struct StringHash {
        using transparent_key_equal = std::equal_to<>;
        using hash_type = std::hash<std::string_view>;

        size_t operator()(std::string_view txt) const { return hash_type{}(txt); }

        size_t operator()(const std::string &txt) const { return hash_type{}(txt); }

        size_t operator()(const char *txt) const { return hash_type{}(txt); }
    };

    static inline size_t utf8_get_byte_num(const char *start, const char *end, size_t word_num) {
        const uint8_t kUTF8SizeTable[] =
                {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                        4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0,
                };

        size_t byte_num = 0;
        for (; word_num > 0; --word_num) {
            if (unlikely(start >= end)) {
                return 0;
            }
            uint8_t word_byte_num = kUTF8SizeTable[static_cast<uint8_t>(*start)];
            if (unlikely(word_byte_num == 0)) {
                return 0;
            }
            byte_num += word_byte_num;
            start += word_byte_num;
        }
        if (unlikely(start > end)) {
            return 0;
        } else {
            return byte_num;
        }
    }
}

#endif //LIBZCW_WORD_H
