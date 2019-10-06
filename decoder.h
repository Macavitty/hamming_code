#ifndef HAMMING_CODE_DECODER_H
#define HAMMING_CODE_DECODER_H

#include <vector>
#include <iostream>


class Decoder {
public:
    std::vector<std::vector<bool>> decode(int distance, const std::vector<std::vector<bool>>& messages);
    std::vector<int> get_syndromes();
    std::vector<bool> get_parities();
private:
    std::vector<int> m_syndromes;
    std::vector<bool> m_parities;
    std::vector<std::vector<bool>> m_fixed_bits;
    std::vector<std::vector<bool>> decode3(const std::vector<std::vector<bool>>& messages);
    std::vector<std::vector<bool>> decode4(const std::vector<std::vector<bool>>& messages);
    void count_syndromes(int t_bit_to_check);
    void count_general_parity();
    void fix();
    void fix(int row);
    void remove_controls();
};


#endif //HAMMING_CODE_DECODER_H
