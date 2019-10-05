#include "coder.h"
using namespace std;

inline bool is_pow_of_two(unsigned a) {
    return (a & (a - 1)) == 0;
}

inline bool get_bit_on_position(unsigned num, unsigned pos) {
//    cout << "Get bit" << endl;
//    cout << "num: " << num << " pos: " << pos << endl;
    unsigned bit = (num >> pos) & 1;
//    cout << "bit: " << bit << endl;
    return bit;
}

Coder::Coder(int t_msgs, int t_distance) : m_messages(t_msgs), m_distance(t_distance) {
    init();
}

Coder::Coder() : m_messages(16), m_distance(3) {
    init();
}

void Coder::code() {
    generate_bits();
    if (m_distance == 4){
        generate_extras();
    }
}

void Coder::init() {
    m_data = count_data();
    m_control = count_control();
    m_total = count_total();
}

int Coder::count_control() {
    cout << "Counted control: " << (log2(ceil(log2(m_data + 1)) + 1 + m_data)) << endl;
    return ceil(log2(m_data + 1 + ceil(log2(m_data + 1))));
}

int Coder::count_data() {
    cout << "Counted data: " << ceil(log2(m_messages)) << endl;
    return ceil(log2(m_messages));
}

int Coder::count_total() {
    cout << "Counted total: " << m_control + m_data << endl;
    return m_control + m_data;
}

void Coder::generate_bits() {

    for (int row_idx = 0; row_idx < m_messages; row_idx++ ) {
        /*
         * fill data bits
         * */
        vector<bool> row;
        int data_idx = 0;
        for (int j = 1; j <= m_total; j++) {
            if (is_pow_of_two(j)) {
                row.push_back(0);
            } else {
                row.push_back(get_bit_on_position(row_idx, m_data - 1 - data_idx));
                data_idx++;
            }
        }
        m_bits.push_back(row);


        /*
         * fill control bits
         * */
        for (int r_idx = 1; r_idx < m_total; r_idx *= 2){
            int real_i = r_idx - 1;
            unsigned xor_res = 0;
            int group_ctr = 0;
            for (int j = r_idx - 1; j < m_total ; j++){
                xor_res ^= m_bits[row_idx][j];
                group_ctr++;
                if (group_ctr == r_idx){
                    group_ctr = 0;
                    j += r_idx;
                }
            }
            m_bits[row_idx][real_i] = xor_res;
        }
    }
}

void Coder::generate_extras() {
    for (int i = 0; i < m_messages; i++){
        unsigned r = 0;
        for (int j = 0; j < m_messages; j++) {
            r ^= m_bits[i][j];
        }
        m_extra_controls.push_back(r);
    }
}

vector<vector<bool>> Coder::get_messages() {
    return m_bits;
}

vector<bool> Coder::get_extra() {
    return m_extra_controls;
}