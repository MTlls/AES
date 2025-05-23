#include "libAes.hpp"

void printBlock(vector<uchar> message) {
    for (int row = 0; row < ROW_SIZE; row++) {
        for (int column = 0; column < ROW_SIZE; column++) {
            cout << hex << setw(2) << setfill('0') << (int)message[(row * ROW_SIZE) + column] << " ";
        }
        cout << endl;
    }
}

void printExpandedKey(vector<uchar> key) {
    for (size_t i = 0; i < key.size(); i++) {
        if (i % ROW_SIZE_EXP_KEY == 0) {
            cout << endl;
        }
        // print in hex
        cout << hex << setw(2) << setfill('0') << (int)key[i] << " ";
    }
    cout << endl;
}

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
    #ifdef DEBUG
        cout << "Input:" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif
    addRoundKey(message, key, 0);

    for(int round = 1; round < ROUNDS; round++){
        #ifdef DEBUG
            cout << "Start of Round " << round << endl;
            cout << "=-=-=-=-=-=-" << endl;
            printBlock(message);
            cout << "=-=-=-=-=-=-" << endl;
        #endif
        shiftSubMixColumns(message);
        #ifdef DEBUG
            cout << "After MixColumns" << endl;
            cout << "=-=-=-=-=-=-" << endl;
            printBlock(message);
            cout << "=-=-=-=-=-=-" << endl;
        #endif
        addRoundKey(message, key, round);
    }
    #ifdef DEBUG
        cout << "Start of Round 10" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif

    shiftSubRows(message);

    #ifdef DEBUG
        cout << "After ShiftRows" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif

    addRoundKey(message, key, 10);

    #ifdef DEBUG
        cout << "Output" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif
    return message;
}

vector<uchar> decryptograph(vector<uchar> message, vector<uchar>  key) {

    addRoundKey(message, key, ROUNDS);

    for(int round = ROUNDS - 1; round > 0; round--){
        #ifdef DEBUG
            cout << "Start of Round " << round << endl;
            cout << "=-=-=-=-=-=-" << endl;
            printBlock(message);
            cout << "=-=-=-=-=-=-" << endl;
        #endif
        invShiftSubColumns(message);
        #ifdef DEBUG
            cout << "After MixColumns" << endl;
            cout << "=-=-=-=-=-=-" << endl;
            printBlock(message);
            cout << "=-=-=-=-=-=-" << endl;
        #endif
        addRoundKey(message, key, round);

        invMixColumns(message);
    }
    #ifdef DEBUG
        cout << "Start of Round 10" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif

    invShiftSubColumns(message);

    #ifdef DEBUG
        cout << "After ShiftRows" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif

    addRoundKey(message, key, 0);

    #ifdef DEBUG
        cout << "Output" << endl;
        cout << "=-=-=-=-=-=-" << endl;
        printBlock(message);
        cout << "=-=-=-=-=-=-" << endl;
    #endif
    return message;
}

void expandKey(vector<uchar> key, vector<uchar> &expandedKey){
    uchar tmp0, tmp1, tmp2, tmp3, tmp4; // temporary variables, for unrolling the loop

    for (size_t i = 0; i < Nc; i++) {
        expandedKey[i*ROW_SIZE_EXP_KEY + 0] = key[i*Nc + 0];
        expandedKey[i*ROW_SIZE_EXP_KEY + 1] = key[i*Nc + 1];
        expandedKey[i*ROW_SIZE_EXP_KEY + 2] = key[i*Nc + 2];
        expandedKey[i*ROW_SIZE_EXP_KEY + 3] = key[i*Nc + 3];
    }

    for (unsigned short i = Nc; i < 44; i++) {
        tmp0 = expandedKey[0*ROW_SIZE_EXP_KEY + i - 1];
        tmp1 = expandedKey[1*ROW_SIZE_EXP_KEY + i - 1];
        tmp2 = expandedKey[2*ROW_SIZE_EXP_KEY + i - 1];
        tmp3 = expandedKey[3*ROW_SIZE_EXP_KEY + i - 1];

        if (i % Nc == 0) {
            tmp4 = tmp0;

            tmp0 = sBox[tmp1] ^ rcon[i/Nc];
            tmp1 = sBox[tmp2];
            tmp2 = sBox[tmp3];
            tmp3 = sBox[tmp4];
        }

        expandedKey[0*ROW_SIZE_EXP_KEY + i] = expandedKey[0*ROW_SIZE_EXP_KEY + i - Nc] ^ tmp0;
        expandedKey[1*ROW_SIZE_EXP_KEY + i] = expandedKey[1*ROW_SIZE_EXP_KEY + i - Nc] ^ tmp1;
        expandedKey[2*ROW_SIZE_EXP_KEY + i] = expandedKey[2*ROW_SIZE_EXP_KEY + i - Nc] ^ tmp2;
        expandedKey[3*ROW_SIZE_EXP_KEY + i] = expandedKey[3*ROW_SIZE_EXP_KEY + i - Nc] ^ tmp3;
    }
}

void addRoundKey(vector<uchar> &message, vector<uchar> roundKey, int round){
    int columnKey = round * ROW_SIZE; // the column where the key starts
    // cout << "=-=-=-=-=-=-" << endl;
    // cout << "antes" << endl;
    // printBlock(message);
    // cout << "=-=-=-=-=-=-" << endl;
    // cout << "columnKey = " << columnKey << endl;
    // cout << "=-=-=-=-=-=-" << endl;
    for (size_t i = 0; i < 4; i++) {
        // cout << dec << "bloco[" << 0*ROW_SIZE + i << "] = ";
        // printHex(message[0*ROW_SIZE + i]);
        // cout << endl;
        // cout << dec << "chave[" << 0*ROW_SIZE_EXP_KEY + columnKey + i << "] = ";
        // printHex(roundKey[0*ROW_SIZE_EXP_KEY + columnKey + i]);
        // cout << endl;
        // cout << dec << "bloco[" << 1*ROW_SIZE + i << "] = ";
        // printHex(message[1*ROW_SIZE + i]);
        // cout << endl;
        // cout << dec << "chave[" << 1*ROW_SIZE_EXP_KEY + columnKey + i << "] = ";
        // printHex(roundKey[1*ROW_SIZE_EXP_KEY + columnKey + i]);
        // cout << endl;
        // cout << dec << "bloco[" << 2*ROW_SIZE + i << "] = ";
        // printHex(message[2*ROW_SIZE + i]);
        // cout << endl;
        // cout << dec << "chave[" << 2*ROW_SIZE_EXP_KEY + columnKey + i << "] = ";
        // printHex(roundKey[2*ROW_SIZE_EXP_KEY + columnKey + i]);
        // cout << endl;
        // cout << dec << "bloco[" << 3*ROW_SIZE + i << "] = ";
        // printHex(message[3*ROW_SIZE + i]);
        // cout << endl;
        // cout << dec<<"chave[" << 3*ROW_SIZE_EXP_KEY + columnKey + i << "] = ";
        // printHex(roundKey[3*ROW_SIZE_EXP_KEY + columnKey + i]);
        // cout << endl;
        message[0*ROW_SIZE + i] ^= roundKey[0*ROW_SIZE_EXP_KEY + columnKey + i];
        message[1*ROW_SIZE + i] ^= roundKey[1*ROW_SIZE_EXP_KEY + columnKey + i];
        message[2*ROW_SIZE + i] ^= roundKey[2*ROW_SIZE_EXP_KEY + columnKey + i];
        message[3*ROW_SIZE + i] ^= roundKey[3*ROW_SIZE_EXP_KEY + columnKey + i];
    }
}

void printHex(uchar byte) {
    cout << hex << setw(2) << setfill('0') << (int)byte;
}

void shiftSubMixColumns(vector<uchar> &message){
    uchar tmp[4 * Nc]; // here we store the result of the operation, all at once

    // for each column
    // 2 3 1 1 m0
    // 1 2 3 1 m1
    // 1 1 2 3 m2
    // 3 1 1 2 m3

    // for column 1
        // tmp[0 + i] = sBox2[message[i]] ^ sBox3[message[Nc + i]] ^ sBox[message[2*Nc + i]] ^ sBox[message[3*Nc + i]];
        // tmp[4 + i] = sBox[message[i]] ^ sBox2[message[Nc + i]] ^ sBox3[message[2*Nc + i]] ^ sBox[message[3*Nc + i]];
        // tmp[8 + i] = sBox[message[i]] ^ sBox[message[Nc + i]] ^ sBox2[message[2*Nc + i]] ^ sBox3[message[3*Nc + i]];
        // tmp[12 + i] = sBox3[message[i]] ^ sBox[message[Nc + i]] ^ sBox[message[2*Nc + i]] ^ sBox2[message[3*Nc + i]];
    tmp[0] = sBox2[message[0]] ^ sBox3[message[5]] ^ sBox[message[10]] ^ sBox[message[15]];
    tmp[4] = sBox[message[0]] ^ sBox2[message[5]] ^ sBox3[message[10]] ^ sBox[message[15]];
    tmp[8] = sBox[message[0]] ^ sBox[message[5]] ^ sBox2[message[10]] ^ sBox3[message[15]];
    tmp[12] = sBox3[message[0]] ^ sBox[message[5]] ^ sBox[message[10]] ^ sBox2[message[15]];

    tmp[1] = sBox2[message[1]] ^ sBox3[message[6]] ^ sBox[message[11]] ^ sBox[message[12]];
    tmp[5] = sBox[message[1]] ^ sBox2[message[6]] ^ sBox3[message[11]] ^ sBox[message[12]];
    tmp[9] = sBox[message[1]] ^ sBox[message[6]] ^ sBox2[message[11]] ^ sBox3[message[12]];
    tmp[13] = sBox3[message[1]] ^ sBox[message[6]] ^ sBox[message[11]] ^ sBox2[message[12]];

    tmp[2] = sBox2[message[2]] ^ sBox3[message[7]] ^ sBox[message[8]] ^ sBox[message[13]];
    tmp[6] = sBox[message[2]] ^ sBox2[message[7]] ^ sBox3[message[8]] ^ sBox[message[13]];
    tmp[10] = sBox[message[2]] ^ sBox[message[7]] ^ sBox2[message[8]] ^ sBox3[message[13]];
    tmp[14] = sBox3[message[2]] ^ sBox[message[7]] ^ sBox[message[8]] ^ sBox2[message[13]];

    tmp[3] = sBox2[message[3]] ^ sBox3[message[4]] ^ sBox[message[9]] ^ sBox[message[14]];
    tmp[7] = sBox[message[3]] ^ sBox2[message[4]] ^ sBox3[message[9]] ^ sBox[message[14]];
    tmp[11] = sBox[message[3]] ^ sBox[message[4]] ^ sBox2[message[9]] ^ sBox3[message[14]];
    tmp[15] = sBox3[message[3]] ^ sBox[message[4]] ^ sBox[message[9]] ^ sBox2[message[14]];
    
    
    memcpy(&message[0], &tmp[0], 4 * Nc);
}

void invMixColumns(vector<uchar> &message){
    uchar tmp[4 * Nc];

    tmp[0] = multE[message[0]] ^ multB[message[4]] ^ multD[message[8]] ^ mult9[message[12]];
    tmp[4] = mult9[message[0]] ^ multE[message[4]] ^ multB[message[8]] ^ multD[message[12]];
    tmp[8] = multD[message[0]] ^ mult9[message[4]] ^ multE[message[8]] ^ multB[message[12]];
    tmp[12] = multB[message[0]] ^ multD[message[4]] ^ mult9[message[8]] ^ multE[message[12]];

    tmp[1] = multE[message[1]] ^ multB[message[5]] ^ multD[message[9]] ^ mult9[message[13]];
    tmp[5] = mult9[message[1]] ^ multE[message[5]] ^ multB[message[9]] ^ multD[message[13]];
    tmp[9] = multD[message[1]] ^ mult9[message[5]] ^ multE[message[9]] ^ multB[message[13]];
    tmp[13] = multB[message[1]] ^ multD[message[5]] ^ mult9[message[9]] ^ multE[message[13]];

    tmp[2] = multE[message[2]] ^ multB[message[6]] ^ multD[message[10]] ^ mult9[message[14]];
    tmp[6] = mult9[message[2]] ^ multE[message[6]] ^ multB[message[10]] ^ multD[message[14]];
    tmp[10] = multD[message[2]] ^ mult9[message[6]] ^ multE[message[10]] ^ multB[message[14]];
    tmp[14] = multB[message[2]] ^ multD[message[6]] ^ mult9[message[10]] ^ multE[message[14]];

    tmp[3] = multE[message[3]] ^ multB[message[7]] ^ multD[message[11]] ^ mult9[message[15]];
    tmp[7] = mult9[message[3]] ^ multE[message[7]] ^ multB[message[11]] ^ multD[message[15]];
    tmp[11] = multD[message[3]] ^ mult9[message[7]] ^ multE[message[11]] ^ multB[message[15]];
    tmp[15] = multB[message[3]] ^ multD[message[7]] ^ mult9[message[11]] ^ multE[message[15]];

    memcpy(&message[0], &tmp[0], 4 * Nc);
}

void invShiftSubColumns(vector<uchar> &message){
    uchar tmp[4 * Nc]; // here we store the result of the operation, all at once

    // for each column
    // 2 3 1 1 m0
    // 1 2 3 1 m1
    // 1 1 2 3 m2
    // 3 1 1 2 m3

    // for column 1
        // tmp[0 + i] = sBox2[message[i]] ^ sBox3[message[Nc + i]] ^ sBox[message[2*Nc + i]] ^ sBox[message[3*Nc + i]];
        // tmp[4 + i] = sBox[message[i]] ^ sBox2[message[Nc + i]] ^ sBox3[message[2*Nc + i]] ^ sBox[message[3*Nc + i]];
        // tmp[8 + i] = sBox[message[i]] ^ sBox[message[Nc + i]] ^ sBox2[message[2*Nc + i]] ^ sBox3[message[3*Nc + i]];
        // tmp[12 + i] = sBox3[message[i]] ^ sBox[message[Nc + i]] ^ sBox[message[2*Nc + i]] ^ sBox2[message[3*Nc + i]];
    tmp[0] = invSBox[message[0]];
    tmp[4] = invSBox[message[7]];
    tmp[8] = invSBox[message[10]];
    tmp[12] = invSBox[message[13]];

    tmp[1] = invSBox[message[1]];
    tmp[5] = invSBox[message[4]];
    tmp[9] = invSBox[message[11]];
    tmp[13] = invSBox[message[14]];

    tmp[2] = invSBox[message[2]];
    tmp[6] = invSBox[message[5]];
    tmp[10] = invSBox[message[8]];
    tmp[14] = invSBox[message[15]];

    tmp[3] =  invSBox[message[3]];
    tmp[7] =  invSBox[message[6]];
    tmp[11] = invSBox[message[9]];
    tmp[15] = invSBox[message[12]];    
    
    memcpy(&message[0], &tmp[0], 4 * Nc);
}

void shiftSubRows(vector<uchar> &message) {
    vector<uchar> shiftedMessage;

    for (int row = 0; row < ROW_SIZE; row++) {
        for (int column = 0; column < ROW_SIZE; column++) {
            shiftedMessage.push_back(sBox[message[
                (row * ROW_SIZE) + ((column + row) % ROW_SIZE)
            ]]);
        }
    }

    message = shiftedMessage;
}