#include "libAes.hpp"

void shiftRows(string * message) {
    string shiftedMessage;

    for (int row = 0; row < ROW_SIZE; row++) {
        for (int column = 0; column < ROW_SIZE; column++) {
            shiftedMessage.push_back(message->at(
                (row * ROW_SIZE) + ((column + row) % ROW_SIZE)
            ));
        }   
    }

    *message = shiftedMessage;
}

string cryptograph(string message, string key) {
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

string decryptograph(string message, string key) {
    return " ";
}