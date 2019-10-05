#ifndef HAMMING_CODE_DECODER_H
#define HAMMING_CODE_DECODER_H

#include <vector>
#include <iostream>


class Decoder {
public:
    std::vector<std::vector<bool>> decode(int distance, std::vector<std::vector<bool>> messages);
    std::vector<int> get_syndromes();
private:
    std::vector<int> m_syndromes;
    std::vector<std::vector<bool>> m_fixed_bits;
    std::vector<std::vector<bool>> decode3(std::vector<std::vector<bool>> messages);
    std::vector<std::vector<bool>> decode4(std::vector<std::vector<bool>> messages);
    void count_syndromes();
    void fix();
    void remove_controls();
};


#endif //HAMMING_CODE_DECODER_H
