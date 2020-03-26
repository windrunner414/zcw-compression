#ifndef LIBZCW_ENCODER_DICT_H
#define LIBZCW_ENCODER_DICT_H

#include <unordered_map>

#include "common/dictionary.h"
#include "word.h"

namespace zcw {
    class EncoderDictWord {
    public:
        EncoderDictWord(uint16_t code, size_t map_size) : code_(code), map_(map_size) {

        }
    private:
        uint16_t code_;
        std::unordered_map<std::string, uint16_t, StringHash, StringHash::transparent_key_equal> map_;

        friend class EncoderDict;
        friend class Encoder;
    };

    class EncoderDict {
    public:
        bool load(const char *dictionary_data, size_t dictionary_size);

    private:
        std::unordered_map<std::string, EncoderDictWord, StringHash, StringHash::transparent_key_equal> map_;

        friend class Encoder;
    };
}

#endif //LIBZCW_ENCODER_DICT_H
