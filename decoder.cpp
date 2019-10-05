#include "decoder.h"

using namespace std;

inline bool is_pow_of_two(unsigned a) {
    return (a & (a - 1)) == 0;
}

vector<vector<bool>> Decoder::decode(int distance, vector<vector<bool>> messages) {
    cout << "decode" << endl;
    m_fixed_bits = messages;
    if (distance == 3) return decode3(messages);
    if (distance == 4) return decode4(messages);
    return vector<vector<bool>>();
}

vector<vector<bool>> Decoder::decode3(vector<vector<bool>> messages) {
    cout << "decode 3" << endl;
    count_syndromes();
    fix();
    remove_controls();
    return m_fixed_bits;
}

vector<vector<bool>> Decoder::decode4(vector<vector<bool>> messages) {
    cout << "decode 4\nreturns new vector" << endl;
    return vector<vector<bool>>();
}

vector<int> Decoder::get_syndromes() {
    cout << "get_syndromes" << endl;
//    decode(distance, messages);
    return m_syndromes;
}

void Decoder::count_syndromes() {
    cout << "count_syndromes" << endl;
    int total = m_fixed_bits[0].size();
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

void Decoder::fix() {
    cout << "fix" << endl;
    for (int i = 0; i < m_syndromes.size(); i++) {
        cout << m_syndromes[i] << " ";
    }
    cout << endl;
    for (auto i = 0; i < m_syndromes.size(); i++) {
        if (m_syndromes[i]) {
            bool bit = m_fixed_bits[i][m_syndromes[i] - 1];
            bit = !bit;
            m_fixed_bits[i][m_syndromes[i] - 1] = bit;
        }
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
