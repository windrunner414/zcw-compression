#ifndef LIBZCW_ZCW_H
#define LIBZCW_ZCW_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZCW_VERSION_MAJOR   1
#define ZCW_VERSION_MINOR   0
#define ZCW_VERSION_RELEASE 1

#define ZCW_MAGIC_NUMBER     0xEA8CD09F
#define ZCW_MAGIC_DICTIONARY 0xBF32D2A7

#ifndef ZCWLIB_VISIBILITY
#  if defined(__GNUC__) && (__GNUC__ >= 4)
#    define ZCWLIB_VISIBILITY __attribute__ ((visibility ("default")))
#  else
#    define ZCWLIB_VISIBILITY
#  endif
#endif
#if defined(ZCW_DLL_EXPORT) && (ZCW_DLL_EXPORT==1)
#  define ZCWLIB_API __declspec(dllexport) ZCWLIB_VISIBILITY
#elif defined(ZCW_DLL_IMPORT) && (ZCW_DLL_IMPORT==1)
#  define ZCWLIB_API __declspec(dllimport) ZCWLIB_VISIBILITY
#else
#  define ZCWLIB_API ZCWLIB_VISIBILITY
#endif

struct ZcwEncoderDict;
ZCWLIB_API ZcwEncoderDict *ZcwLoadEncoderDict(const char *dict_data, size_t dict_size);
ZCWLIB_API void ZcwFreeEncoderDict(ZcwEncoderDict *dict);

struct ZcwEncoder;
ZCWLIB_API ZcwEncoder *ZcwCreateEncoder(const ZcwEncoderDict *dict, const char *src, size_t src_size);
ZCWLIB_API void ZcwFreeEncoder(ZcwEncoder *encoder);
ZCWLIB_API unsigned short ZcwEncoderIsReady(const ZcwEncoder *encoder);
ZCWLIB_API unsigned short ZcwEncoderIsFinished(const ZcwEncoder *encoder);
ZCWLIB_API unsigned short ZcwEncoderIsFailed(const ZcwEncoder *encoder);
ZCWLIB_API size_t ZcwGetEncodeBound(const ZcwEncoder *encoder);
ZCWLIB_API size_t ZcwEncode(ZcwEncoder *encoder, char *dst, size_t dst_capacity);

struct ZcwDecoderDict;
ZCWLIB_API ZcwDecoderDict *ZcwLoadDecoderDict(const char *dict_data, size_t dict_size);
ZCWLIB_API void ZcwFreeDecoderDict(ZcwDecoderDict *dict);

struct ZcwDecoder;
ZCWLIB_API ZcwDecoder *ZcwCreateDecoder(const ZcwDecoderDict *dict, const char *src, size_t src_size);
ZCWLIB_API void ZcwFreeDecoder(ZcwDecoder *decoder);
ZCWLIB_API unsigned short ZcwDecoderIsReady(const ZcwDecoder *decoder);
ZCWLIB_API unsigned short ZcwDecoderIsFinished(const ZcwDecoder *decoder);
ZCWLIB_API unsigned short ZcwDecoderIsFailed(const ZcwDecoder *decoder);

#ifdef __cplusplus
}
#endif

#endif //LIBZCW_ZCW_H