#ifndef LIBZCW_DECODER_H
#define LIBZCW_DECODER_H

#include "decoder_dict.h"

namespace zcw {
    enum class DecoderState {
        READY,
        FAILED,
        FINISHED,
    };

    class Decoder {
    public:
        Decoder(const DecoderDict *dictionary, const char *src, size_t src_size);

        size_t decode(char *dst, size_t dst_capacity);

        [[nodiscard]] bool isFailed() const {
            return state_ == DecoderState::FAILED;
        }

        [[nodiscard]] bool isFinished() const {
            return state_ == DecoderState::FINISHED;
        }

        [[nodiscard]] bool isReady() const {
            return state_ == DecoderState::READY;
        }

        [[nodiscard]] DecoderState getState() const {
            return state_;
        }

    private:
        const DecoderDict *dictionary_;
        const char *src_;
        const size_t src_size_;
        DecoderState state_;
    };
}


#endif //LIBZCW_DECODER_H
