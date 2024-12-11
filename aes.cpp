#include "libAes.hpp"

vector<uchar> readFile(ifstream &file) {
    uchar content[16];
    vector<uchar> block(16);
    int lidos = 0;

    while (file.good()) {
        file.read((char *)&content, 16);
        lidos = file.gcount();
        
        if (lidos == 0) {
            break;
        }
        
        for (int i = 0, k = 0; i < 4; i++) {
            block[i +  0] = content[k++];
            block[i +  4] = content[k++];
            block[i +  8] = content[k++];
            block[i + 12] = content[k++];
        }
    }

    return block;
}

void writeFile(ofstream &file, vector<uchar> block) {
    for (int i = 0; i < Nc; i++) {
        file << block[i];
        file << block[ROW_SIZE + i];
        file << block[2*ROW_SIZE + i];
        file << block[3*ROW_SIZE + i];
    }
}

int main(int argc, char **argv){
    string output_file = "";
    if(argc < 3){
        cerr << "Usage: " << argv[0] << " <input_file> <key> <output_file>" << endl;
        exit(1);
    } else if (argc != 3){
        output_file = argv[3];
    }
    string input_file = argv[1];
    string key_file = argv[2];

    // TODO: jogar isso para dentro da função de criptografia ou descriptografia
    ifstream filestream(input_file, ios::binary);
    ifstream keyfilestream(key_file, ios::binary);
    ofstream output_filestream;


    vector<uchar> message;
    vector<uchar> key; 
    key = readFile(keyfilestream);
    vector<uchar> expKey(176);
    expandKey(key, expKey);
    
    if(!output_file.empty()){
        output_filestream.open(output_file, ios::binary);
    } else {
        // output_filestream to stdout
        output_filestream.basic_ios<char>::rdbuf(cout.rdbuf());
    }

    while(filestream.good()){
        message = readFile(filestream);
        message = decryptograph(message, expKey);
        writeFile(output_filestream, message);
    }
    // decryptograph(message, key);

    return 0;
}