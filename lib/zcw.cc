#include "zcw.h"
#include "enc/encoder.h"

struct ZcwEncoderDict {
    zcw::EncoderDict dict;
};

struct ZcwEncoder {
    ZcwEncoder(const ZcwEncoderDict *dict, const char *src, size_t src_size)
            : encoder(&(dict->dict), src, src_size) {
    }

    zcw::Encoder encoder;
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
