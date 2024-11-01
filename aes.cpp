#include <openssl/evp.h>
#include <bits/stdc++.h>
#include <aes.hpp>
using namespace std;

int main(int argc, char **argv){    
    string output_file = "output";
    if(argc < 3){
        cerr << "Usage: " << argv[0] << " <input_file> <key> <output_file>" << endl;
        exit(1);
    } else if (argc != 3){
        output_file = argv[3];
    }
    string input_file = argv[1];

}