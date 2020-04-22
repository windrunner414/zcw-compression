#include "encoder_dict.h"

/// if index is invalid, return 0
static inline uint16_t index_to_code(uint16_t index) {
    if (index <= zcw::kOneByteCodeNum) {
        return index;
    } else if (index <= zcw::kOneByteCodeNum + zcw::kTwoByteCodeNum) {
        return static_cast<uint16_t>(index - zcw::kOneByteCodeNum - 1) | (0b11U << 14U);
    } else {
        return 0;
    }
}

bool zcw::EncoderDict::load(const char *dictionary_data, size_t dictionary_size) {
    const char *p = dictionary_data;
    const char *p_end = dictionary_data + dictionary_size;
    uint16_t first_level_index = 1;

    uint16_t index_level_map_size = *reinterpret_cast<const uint16_t *>(p);
    if (!is_little_endian()) {
        index_level_map_size = bswap_16(index_level_map_size);
    }
    p += 2;
    if (index_level_map_size > kOneByteCodeNum + kTwoByteCodeNum) {
        return false;
    }

    for (; p < p_end;) {
        if (first_level_index > index_level_map_size) {
            return false;
        }

        uint8_t word_num = *p;
        if (word_num == 0) {
            return false;
        }
        const char *word = ++p;
        size_t word_len = utf8_get_byte_num(word, p_end, word_num);
        if (word_len == 0) {
            return false;
        }
        p += word_len;

        if (p + 1 >= p_end) {
            return false;
        }
        uint16_t second_level_map_size = *reinterpret_cast<const uint16_t *>(p);
        if (!is_little_endian()) {
            second_level_map_size = bswap_16(second_level_map_size);
        }
        p += 2;
        if (second_level_map_size > kOneByteCodeNum + kTwoByteCodeNum) {
            return false;
        }

        uint16_t code = index_to_code(first_level_index++);
        if (code == 0) {
            return false;
        }
        auto result = map_.emplace(std::piecewise_construct, std::forward_as_tuple(word, word_len),
                                   std::forward_as_tuple(code, second_level_map_size));
        if (!result.second) {
            return false;
        }
        auto &second_level_map = result.first->second.map_;

        uint16_t second_level_index = 1;
        for (; second_level_map_size > 0; --second_level_map_size) {
            if (p >= p_end) {
                return false;
            }

            word_num = *p;
            if (word_num == 0) {
                return false;
            }
            word = ++p;
            word_len = utf8_get_byte_num(word, p_end, word_num);
            if (word_len == 0) {
                return false;
            }
            p += word_len;

            code = index_to_code(second_level_index++);
            if (code == 0) {
                return false;
            }
            if (!second_level_map.emplace(std::piecewise_construct, std::forward_as_tuple(word, word_len),
                                          std::forward_as_tuple(code)).second) {
                return false;
            }
        }
    }

    return first_level_index == (index_level_map_size + 1);
}
