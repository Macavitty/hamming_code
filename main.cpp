#include <iostream>
#include "coder.h"
#include "decoder.h"

using namespace std;

int get_distance() {
    string input;
    while (true) {
        cout << "Enter m_distance value  or <q> to quit" << endl;
        cin >> input;
        if (input == "3" || input == "4") {
            return stoi(input);
        }
        if (input == "q")
            return -1;
        cout << "Wrong m_distance. Expected 3 or 4." << endl;
        cout << "Try again or quit" << endl;
    }

}

int get_msg_count() {
    string input;
    cout << "Enter count of messages value  or <q> or <Q> to quit:" << endl;
    while (true) {
        cin >> input;
        if (input == "q" || input == "Q")
            return -1;
        int count = stoi(input);
        if (count > 0) {
            return count;
        }
        cout << "Wrong count of messages. Expected positive integer." << endl;
        cout << "Try again or quit:" << endl;
    }

}

int main() {
    int msg_count, distance;
    int input;
    cout << ". . . Some info about programme and hamming" << endl;

    distance = get_distance();
    if (distance < 0) {
        cout << "Quit . . ." << endl;
        return 0;
    }
    msg_count = get_msg_count();
    if (msg_count < 0) {
        cout << "Quit . . ." << endl;
        return 0;
    }

    Coder coder(msg_count, distance);
    coder.code();

    vector<vector<bool>> msgs = coder.get_messages();
    vector<bool> extra = coder.get_extra();

    // cout
    cout << "Possible messages:" << endl;
    for (auto i = 0; i < msgs.size(); i++) {
        cout << i << ":\t [ ";
        for (auto j = 0; j < msgs[0].size(); j++) {
            cout << msgs[i][j] << " ";
        }
        if (extra.size() != 0) {
            cout << "] extra : " << extra[i];
        } else { cout << "]"; }
        cout << endl;
    }

    /*
     * spoiling some bits:
     * */
//    msgs[0][4] = 1; // i = 0: 0 -> 4
//    msgs[0][6] = 1; // i = 0: 4 -> 6
//    msgs[2][5] = 0; // i = 2: 2-> 0
//    msgs[15][2] = 0; // i = 2: 2-> 0
//    msgs[11][6] = 0; // i = 2: 2-> 0

    /*
     * and let decoder to fix it
     * */
    Decoder decoder;
    vector<vector<bool>> decoded_msg = decoder.decode(distance, msgs);
    vector<int> syndromes = decoder.get_syndromes();
    vector<bool> parities;
    if (distance == 4)
        parities = decoder.get_parities();
    //cout
    cout << "Decoded messages:" << endl;
    for (auto i = 0; i < decoded_msg.size(); i++){
        cout << i << ":\t[ ";
        for (auto j = 0; j < decoded_msg[0].size(); j++){
            cout <<  decoded_msg[i][j] << " ";
        }
        cout << "]\tsyndrome: " << syndromes[i];
        if (distance == 4){
            cout << "\tparity: " << parities[i] << endl;
        } else cout << endl;
    }
    return 0;
}


