#include <iostream>
#include "src/Lexer/Lexer.h"

#include <fstream>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Requires an input file path. Exiting...";
        exit(1);
    }

    std::string filePath = argv[1];

    std::map<std::string, Sequence> environment_sequences;
    Lexer lexer;

    std::ifstream file;
    file.open(filePath);

    if (file.is_open()) {
        lexer.run(file);
    }

    return 0;
}