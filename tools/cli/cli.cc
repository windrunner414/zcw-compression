#include <iostream>
#include <fstream>
#include <ctime>

#include "zcw.h"

int main() {
    printf("zcw version %d.%d.%d\n", ZCW_VERSION_MAJOR, ZCW_VERSION_MINOR, ZCW_VERSION_RELEASE);

    std::ifstream dict(R"(C:\Users\windr\CLionProjects\zcw-compression\tools\dictionary_generator\dictionary)", std::ifstream::binary);
    dict.seekg(0, std::ifstream::end);
    size_t dict_size = dict.tellg();
    dict.seekg(0, std::ifstream::beg);
    char *dict_data = new char[dict_size];
    dict.read(dict_data, dict_size);
    clock_t start = clock();
    auto encoder_dict = ZcwLoadEncoderDict(dict_data, dict_size);
    clock_t end = clock();
    std::cout << "load dict: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
    delete[] dict_data;
    if (encoder_dict == nullptr) {
        printf("load dictionary failed\n");
    } else {
        printf("load dictionary: %d bytes\n", dict_size);
    }

    std::ifstream input(R"(C:\Users\windr\CLionProjects\zcw-compression\tools\cli\input.txt)");
    input.seekg(0, std::ifstream::end);
    size_t src_size = input.tellg();
    printf("src size: %d\n", src_size);
    input.seekg(0, std::ifstream::beg);
    char *src = new char[src_size];
    memset(src, 0, src_size);
    input.read(src, src_size);
    std::cout << std::hash<std::string_view>{}(std::string_view(src,src_size)) << std::endl;
    auto *encoder = ZcwCreateEncoder(encoder_dict, src, src_size);
    printf("%d,%d,%d\n",ZcwEncoderIsFailed(encoder), ZcwEncoderIsReady(encoder), ZcwEncoderIsFinished(encoder));
    size_t max_size = ZcwGetEncodeBound(encoder);
    auto *dst = new char[max_size];
    size_t size = ZcwEncode(encoder, dst, max_size);
    std::ofstream output(R"(C:\Users\windr\CLionProjects\zcw-compression\tools\cli\compressed.txt)", std::ofstream::binary);
    output.write(dst, size);

    printf("compressed size: %d, error: %d, ready: %d, finish: %d", size, ZcwEncoderIsFailed(encoder), ZcwEncoderIsReady(encoder), ZcwEncoderIsFinished(encoder));

    delete[] src;
    delete[] dst;
    ZcwFreeEncoder(encoder);
    ZcwFreeEncoderDict(encoder_dict);

    return 0;
}
