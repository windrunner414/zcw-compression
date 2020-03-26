#ifndef LIBZCW_ENCODER_H
#define LIBZCW_ENCODER_H

#include "encoder_dict.h"

namespace zcw {
    enum class EncoderState {
        READY,
        FAILED,
        FINISHED,
    };

    class Encoder {
    public:
        Encoder(const EncoderDict *dictionary, const char *src, size_t src_size);

        /// maximum size after encoding in the worst case
        /// if all words not in the dictionary, add \0 before every word
        /// and all words is 1byte ASCII, the size will double
        [[nodiscard]] size_t getEncodeBound() const {
            // TODO: 计算metadata长度
            return src_size_ * 2;
        }

        size_t encode(char *dst, size_t dst_capacity);

        [[nodiscard]] bool isFailed() const {
            return state_ == EncoderState::FAILED;
        }

        [[nodiscard]] bool isFinished() const {
            return state_ == EncoderState::FINISHED;
        }

        [[nodiscard]] bool isReady() const {
            return state_ == EncoderState::READY;
        }

        [[nodiscard]] EncoderState getState() const {
            return state_;
        }

    private:
        const EncoderDict *dictionary_;
        const char *src_;
        size_t src_size_;
        EncoderState state_;
        const char *current_pos_;
        const char *end_pos_;
    };
}

#endif //LIBZCW_ENCODER_H
