#ifndef LIBZCW_DECODER_DICT_H
#define LIBZCW_DECODER_DICT_H


namespace zcw {
    class DecoderDict {
    public:
        bool load(const char *dictionary_data, size_t dictionary_size);
    };
}


#endif //LIBZCW_DECODER_DICT_H
