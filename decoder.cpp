#include "decoder.h"

using namespace std;

inline bool is_pow_of_two(unsigned a) {
    return (a & (a - 1)) == 0;
}

vector<vector<bool>> Decoder::decode(int distance, const vector<vector<bool>> &messages) {
    m_fixed_bits = messages;
    if (distance == 3) return decode3(messages);
    if (distance == 4) return decode4(messages);
    return vector<vector<bool>>();
}

vector<vector<bool>> Decoder::decode3(const vector<vector<bool>>& messages) {
    count_syndromes(m_fixed_bits[0].size());
    fix();
    remove_controls();
    return m_fixed_bits;
}

vector<vector<bool>> Decoder::decode4(const vector<vector<bool>> &messages) {
    count_syndromes(m_fixed_bits[0].size());
    count_general_parity();
    // fix if we can
    for (auto i = 0; i < m_fixed_bits.size(); i++) {
        if (m_syndromes[i]){
            if (m_parities[i]) fix(i);
        }
    }
    remove_controls();
    return m_fixed_bits;
}

vector<int> Decoder::get_syndromes() {
    return m_syndromes;
}

void Decoder::count_syndromes(int t_bit_to_check) {
    int total = t_bit_to_check;
    int msg_count = m_fixed_bits.size();
    for (int i = 0; i < msg_count; i++) {  // for all messages
        cout << "-- ROW " << i << " --" << endl;
        unsigned syndrome = 0;
        unsigned high_bit_idx = 0;
        for (int r_idx = 1; r_idx < total; r_idx *= 2) { // for each control bit in message
            cout << "r: " << r_idx << endl << "xor:\n";
            unsigned xor_res = 0;
            int group_ctr = 0;
            for (int j = r_idx - 1; j < total; j++) { // get all bits (controls and data) that form Sj
                cout << "j: " << j << " xor_res: " << xor_res << " bit_to_add: " << m_fixed_bits[i][j] << endl;
                xor_res ^= m_fixed_bits[i][j];
                group_ctr++;
                if (group_ctr == r_idx) {
                    group_ctr = 0;
                    j += r_idx;
                }
            }
            cout << "high: " << high_bit_idx << endl;
            xor_res <<= high_bit_idx;
            syndrome |= xor_res;
            cout << "syndrome: " << syndrome << endl;
            high_bit_idx++;
        }
        m_syndromes.push_back(syndrome);
    }
}

void Decoder::count_general_parity() {
    for (auto &row : m_fixed_bits) {
        int parity = 0;
        for (auto j = 0; j < m_fixed_bits[0].size(); j++) {
            parity += row[j];

        }
        parity %= 2;
        m_parities.push_back(parity);
    }
}


void Decoder::fix() {
    for (int i = 0; i < m_syndromes.size(); i++) {
        fix(i);
    }
}

void Decoder::fix(int row) {
    if (m_syndromes[row]) {
        bool bit = m_fixed_bits[row][m_syndromes[row] - 1];
        bit = !bit;
        m_fixed_bits[row][m_syndromes[row] - 1] = bit;
    }

}


void Decoder::remove_controls() {
    cout << "remove_controls" << endl;
    auto msg_cnt = m_fixed_bits[0].size();
    vector<bool> new_row;
    for (auto i = 0; i < m_fixed_bits.size(); i++) {
        for (int j = 0; j < msg_cnt; j++) {
            if (!is_pow_of_two(j + 1))
                new_row.push_back(m_fixed_bits[i][j]);
        }
        m_fixed_bits.erase(m_fixed_bits.begin() + i); // replace() not found ¯\_(ツ)_/¯
        m_fixed_bits.insert(m_fixed_bits.begin() + i, new_row);
        new_row.clear();
    }
}

vector<bool> Decoder::get_parities() {
    return m_parities;
}
