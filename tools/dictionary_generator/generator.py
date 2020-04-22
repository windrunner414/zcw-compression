# -*- coding: utf-8 -*-

DICT_MAX_CODE = 16575


def prepare_words(file):
    import jieba
    return jieba.cut(file.read())


def generate(args):
    from collections import Counter
    words = Counter()
    bi_gram = {}

    for file in args.corpus:
        p_word = ''
        for word in prepare_words(file):
            if len(word) > 255:
                p_word = ''
                continue
            words[word] += 1
            if p_word != '':
                if p_word not in bi_gram.keys():
                    bi_gram[p_word] = Counter()
                bi_gram[p_word][word] += 1
            p_word = word

    with open(args.output, 'wb') as output_file:
        output_words = words.most_common(DICT_MAX_CODE)
        output_file.write(len(output_words).to_bytes(2, byteorder='little', signed=False))

        for e in output_words:
            word = e[0]
            output_file.write(len(word).to_bytes(1, byteorder='little', signed=False))
            output_file.write(word.encode('utf-8'))

            if word in bi_gram.keys():
                n_word_list = bi_gram[word].most_common(DICT_MAX_CODE)
                output_file.write(len(n_word_list).to_bytes(2, byteorder='little', signed=False))
                for ne in n_word_list:
                    n_word = ne[0]
                    output_file.write(len(n_word).to_bytes(1, byteorder='little', signed=False))
                    output_file.write(n_word.encode('utf-8'))
            else:
                output_file.write(bytes([0, 0]))  # uint16_t 0


if __name__ == '__main__':
    import argparse
    arg_parser = argparse.ArgumentParser(description='use to generate dictionaries for zcw')
    arg_parser.add_argument('--output', '-o', type=str, dest='output',
                            default='dictionary', help='output dictionary file')
    arg_parser.add_argument('corpus', type=argparse.FileType('r', encoding='utf-8', errors='strict'),
                            help='input utf-8 corpus file[s]', nargs='+')
    generate(arg_parser.parse_args())
