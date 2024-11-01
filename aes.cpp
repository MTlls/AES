#include "libAes.hpp"

int main(int argc, char **argv){
    string output_file = "output";
    if(argc < 3){
        cerr << "Usage: " << argv[0] << " <input_file> <key> <output_file>" << endl;
        exit(1);
    } else if (argc != 3){
        output_file = argv[3];
    }
    string input_file = argv[1];

    // TODO: extrair mensagem e chave dos arquivos
    string message = "abcdefghijklmnopqrstuvwxyz";
    string key = "0123456789012345"; 

    cryptograph(message, key);
    decryptograph(message, key);

    return 0;
}