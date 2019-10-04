#ifndef HAMMING_CODE_CODER_H
#define HAMMING_CODE_CODER_H

#include <cmath>
#include <vector>
#include <iostream> // get rid off this in the end

class Coder{
private:
    int m_messages; // amount of possible messages
    int m_distance; // distance
    int m_total = -1; // total number of bits
    int m_control = -1; // control bits count
    int m_data = -1; // data bits count
    std::vector<std::vector<bool>> bits;
    std::vector<bool> extra_controls;
    int count_control();
    int count_data();
    int count_total();
    void init();
    void generate_bits();
    void generate_extras();
public:
    Coder();
    Coder(int t_msgs, int t_distance);
    void code();
    std::vector<std::vector<bool>> get_messages();
    std::vector<bool> get_extra();
};


#endif //HAMMING_CODE_CODER_H
