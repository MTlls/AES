#ifndef AES_H
#define AES_H

#include <bits/stdc++.h>

#define ROUNDS_QUANTITY 10
#define BLOCK_SIZE 16
#define ROW_SIZE 4

using namespace std;

string cryptograph(string message, string key);
string decryptograph(string message, string key);

#endif