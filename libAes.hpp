#ifndef AES_H
#define AES_H

#include <bits/stdc++.h>
#include "tables.hpp"

#define ROUNDS 10
#define BLOCK_SIZE 16
#define ROW_SIZE 4
#define Nc 4 //columns in the key
#define ROW_SIZE_EXP_KEY 44

typedef unsigned char uchar;

using namespace std;

vector<uchar> cryptograph(vector<uchar>  message, vector<uchar>  key);
vector<uchar> decryptograph(vector<uchar>  message, vector<uchar>  key);
void expandKey(vector<uchar>  key, vector<uchar> &expandedKey);
void addRoundKey(vector<uchar> &message, vector<uchar> roundKey, int round);
void printHex(uchar byte);
void shiftSubMixColumns(vector<uchar> &message);
void shiftSubRows(vector<uchar> &message);

void printBlock(vector<uchar> message);
void printExpandedKey(vector<uchar> key);

#endif