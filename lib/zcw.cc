#include "zcw.h"
#include "enc/encoder.h"
#include "dec/decoder.h"

struct ZcwEncoderDict {
    zcw::EncoderDict dict;
};

ZCWLIB_API ZcwEncoderDict *ZcwLoadEncoderDict(const char *dict_data, size_t dict_size) {
    auto *dict = new ZcwEncoderDict;
    if (dict->dict.load(dict_data, dict_size)) {
        return dict;
    } else {
        ZcwFreeEncoderDict(dict);
        return nullptr;
    }
}

ZCWLIB_API void ZcwFreeEncoderDict(ZcwEncoderDict *dict) {
    delete dict;
}

struct ZcwEncoder {
    ZcwEncoder(const ZcwEncoderDict *dict, const char *src, size_t src_size)
            : encoder(&(dict->dict), src, src_size) {
    }

    zcw::Encoder encoder;
};

ZCWLIB_API ZcwEncoder *ZcwCreateEncoder(const ZcwEncoderDict *dict, const char *src, size_t src_size) {
    return new ZcwEncoder(dict, src, src_size);
}

ZCWLIB_API void ZcwFreeEncoder(ZcwEncoder *encoder) {
    delete encoder;
}

ZCWLIB_API unsigned short ZcwEncoderIsReady(const ZcwEncoder *encoder) {
    return encoder->encoder.isReady();
}

ZCWLIB_API unsigned short ZcwEncoderIsFinished(const ZcwEncoder *encoder) {
    return encoder->encoder.isFinished();
}

ZCWLIB_API unsigned short ZcwEncoderIsFailed(const ZcwEncoder *encoder) {
    return encoder->encoder.isFailed();
}

ZCWLIB_API size_t ZcwGetEncodeBound(const ZcwEncoder *encoder) {
    return encoder->encoder.getEncodeBound();
}

ZCWLIB_API size_t ZcwEncode(ZcwEncoder *encoder, char *dst, size_t dst_capacity) {
    return encoder->encoder.encode(dst, dst_capacity);
}

struct ZcwDecoderDict {
    zcw::DecoderDict dict;
};

ZCWLIB_API ZcwDecoderDict *ZcwLoadDecoderDict(const char *dict_data, size_t dict_size) {
    auto *dict = new ZcwDecoderDict;
    if (dict->dict.load(dict_data, dict_size)) {
        return dict;
    } else {
        ZcwFreeDecoderDict(dict);
        return nullptr;
    }
}

ZCWLIB_API void ZcwFreeDecoderDict(ZcwDecoderDict *dict) {
    delete dict;
}

struct ZcwDecoder {
    ZcwDecoder(const ZcwDecoderDict *dict, const char *src, size_t src_size)
            : decoder(&(dict->dict), src, src_size) {
    }

    zcw::Decoder decoder;
};

ZCWLIB_API ZcwDecoder *ZcwCreateDecoder(const ZcwDecoderDict *dict, const char *src, size_t src_size) {
    return new ZcwDecoder(dict, src, src_size);
}

ZCWLIB_API void ZcwFreeDecoder(ZcwDecoder *decoder) {
    delete decoder;
}

ZCWLIB_API unsigned short ZcwDecoderIsReady(const ZcwDecoder *decoder) {
    return decoder->decoder.isReady();
}

ZCWLIB_API unsigned short ZcwDecoderIsFinished(const ZcwDecoder *decoder) {
    return decoder->decoder.isFinished();
}

ZCWLIB_API unsigned short ZcwDecoderIsFailed(const ZcwDecoder *decoder) {
    return decoder->decoder.isFailed();
}
