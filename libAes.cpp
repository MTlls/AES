#include "libAes.hpp"

void shiftRows(vector<uchar> *message) {
    vector<uchar> shiftedMessage;

    for (int row = 0; row < ROW_SIZE; row++) {
        for (int column = 0; column < ROW_SIZE; column++) {
            shiftedMessage.push_back(message->at(
                (row * ROW_SIZE) + ((column + row) % ROW_SIZE)
            ));
        }
    }

    *message = shiftedMessage;
}

vector<uchar> cryptograph(vector<uchar> message, vector<uchar> key) {
    /*
    //addRoundKey(message, key);
    string roundKey;
    for(int round = 0; round < ROUNDS_QUANTITY; round++) {
    //    roundKey = getRoundKey(key, round);
    //    shiftRows(message);
    //    mixColumns(message);
    //    addRoundKey(message, roundKey);
    }

    return " ";
    */
   shiftRows(&message);
   return message;
}

vector<uchar>  decryptograph(vector<uchar>  message, vector<uchar>  key) {
    // null for now
    return vector<uchar>();
}

void expandKey(vector<uchar> key, vector<uchar> &expandedKey){
    uchar tmp0, tmp1, tmp2, tmp3, tmp4; // temporary variables, for unrolling the loop
    for (size_t i = 0; i < Nc; i++) {
        expandedKey[0*Nc + i] = key[Nc*i + 0];
        expandedKey[1*Nc + i] = key[Nc*i + 1];
        expandedKey[2*Nc + i] = key[Nc*i + 2];
        expandedKey[3*Nc + i] = key[Nc*i + 3];
    }

    for (unsigned short i = Nc; i < 44; i++) {
        // rotates the key
        // [b0, b1, b2, b3] -> [b1, b2, b3, b0]
        tmp0 = expandedKey[4*i - 4];
        tmp1 = expandedKey[4*i - 3];
        tmp2 = expandedKey[4*i - 2];
        tmp3 = expandedKey[4*i - 1];

        if (i % Nc == 0) {
            tmp4 = tmp0;

            tmp0 = sbox[tmp1] ^ rcon[i/Nc];
            tmp1 = sbox[tmp2];
            tmp2 = sbox[tmp3];
            tmp3 = sbox[tmp4];
        }

        expandedKey[4*i + 0] = expandedKey[4*(i - Nc) + 0] ^ tmp0;
        expandedKey[4*i + 1] = expandedKey[4*(i - Nc) + 1] ^ tmp1;
        expandedKey[4*i + 2] = expandedKey[4*(i - Nc) + 2] ^ tmp2;
        expandedKey[4*i + 3] = expandedKey[4*(i - Nc) + 3] ^ tmp3;
    }
}