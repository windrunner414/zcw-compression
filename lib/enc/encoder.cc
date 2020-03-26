#include <cassert>

#include "encoder.h"

static inline uint8_t write_code_to_buf(char *dst, const char *dst_end, uint16_t code) {
    char *c_code = reinterpret_cast<char *>(&code);
    if (code >> 8U) {
        if (unlikely(dst_end - dst < 2)) {
            return 0;
        }
        dst[0] = *c_code;
        dst[1] = *(c_code + 1);
        return 2;
    } else {
        if (unlikely(dst_end - dst < 1)) {
            return 0;
        }
        dst[0] = *(c_code + 1);
        return 1;
    }
}

zcw::Encoder::Encoder(const EncoderDict *dictionary, const char *src, size_t src_size)
        : dictionary_(dictionary), src_(src), current_pos_(src),
          end_pos_(src + src_size), src_size_(src_size) {
    if (likely(src != nullptr && src_size > 0)) {
        state_ = EncoderState::READY;
    } else {
        state_ = EncoderState::FAILED;
    }
}

size_t zcw::Encoder::encode(char *dst, size_t dst_capacity) {
    if (unlikely(!isReady())) {
        return 0;
    }

    char *dst_current = dst;
    const char *dst_end = dst + dst_capacity;

    const EncoderDictWord *current_word = nullptr;

    for (; (current_pos_ < end_pos_ && dst_current < dst_end);) {
        const char *word = current_pos_;
        uint16_t code = 0;
        size_t s_word_len = 0;

        for (; current_pos_ < end_pos_;) {
            s_word_len = utf8_get_byte_num(current_pos_, end_pos_, 1);
            if (unlikely(s_word_len == 0)) {
                state_ = zcw::EncoderState::FAILED;
                return 0;
            }
            std::string_view word_str(word, current_pos_ - word + s_word_len);
            if (current_word != nullptr) {
                auto result = current_word->map_.find(word_str);
                if (result == current_word->map_.end()) {
                    if (code != 0) {
                        auto t_result = dictionary_->map_.find(std::string_view(word, current_pos_ - word));
                        if (t_result == dictionary_->map_.end()) {
                            current_word = nullptr;
                        } else {
                            current_word = &t_result->second;
                        }
                    } else {
                        current_word = nullptr;
                        continue;
                    }
                    break;
                } else {
                    current_pos_ += s_word_len;
                    code = result->second;
                }
            } else {
                auto result = dictionary_->map_.find(word_str);
                if (result == dictionary_->map_.end()) {
                    break;
                } else {
                    current_pos_ += s_word_len;
                    code = result->second.code_;
                    current_word = &result->second;
                }
            }
        }

        if (code == 0) {
            // current_pos == word and s_word_len is len of the word which not be found
            if (unlikely(dst_end - dst_current < s_word_len + 1)) {
                return dst_current - dst;
            } else {
                current_pos_ += s_word_len;
                dst_current[0] = 0;
                memcpy(++dst_current, word, s_word_len);
                dst_current += s_word_len;
            }
        } else {
            uint8_t code_byte_num = write_code_to_buf(dst_current, dst_end, code);
            if (likely(code_byte_num > 0)) {
                dst_current += code_byte_num;
            } else {
                current_pos_ = word;
                return dst_current - dst;
            }
        }
    }

    assert(current_pos_ <= end_pos_);
    if (current_pos_ == end_pos_) {
        state_ = EncoderState::FINISHED;
    }
    return dst_current - dst;
}
