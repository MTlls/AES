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
        if (i % 4 == 0) {
            cout << endl;
        }
        // print in hex
        cout << hex << setw(2) << setfill('0') << (int)key[i] << " ";
    }
}

vector<uchar> readFile(string file) {
    ifstream filestream(file, ios::binary);
    vector<uchar> content;

    if (filestream.is_open()) {
        while (filestream.good()) {
            uchar byte;
            filestream.read((char*)&byte, sizeof(byte));
            content.push_back(byte);
        }
    } else {
        cout << "Error when reading file " << file << endl;
    }

    return content;
}

int main(int argc, char **argv){
    string output_file = "output";
    if(argc < 3){
        cerr << "Usage: " << argv[0] << " <input_file> <key> <output_file>" << endl;
        exit(1);
    } else if (argc != 3){
        output_file = argv[3];
    }
    string input_file = argv[1];
    string key_file = argv[2];

    // TODO: extrair mensagem e chave dos arquivos
    vector<uchar> message = readFile(input_file);
    vector<uchar> key = readFile(key_file); 

    cout << "=-=-=-=-=-=-" << endl;
    printBlock(message);
    cout << "=-=-=-=-=-=-" << endl;

    message = cryptograph(message, key);

    cout << "=-=-=-=-=-=-" << endl;
    printBlock(message);
    cout << "=-=-=-=-=-=-" << endl;
    //decryptograph(message, key);

    vector<uchar> expKey(176);
    expandKey(key, expKey);

    return 0;
}