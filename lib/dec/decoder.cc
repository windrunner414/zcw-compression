#include "common/internal.h"
#include "decoder.h"

zcw::Decoder::Decoder(const zcw::DecoderDict *dictionary, const char *src, size_t src_size)
        : dictionary_(dictionary), src_(src), src_size_(src_size) {
    if (likely(src != nullptr && src_size > 0)) {
        state_ = DecoderState::READY;
    } else {
        state_ = DecoderState::FAILED;
    }
}

size_t zcw::Decoder::decode(char *dst, size_t dst_capacity) {
    //todo
    return 0;
}
