#include <iostream>
#include <list>

#include "scanner/Scanner.h"
#include <fstream>

void run(std::string& source) {
    Scanner scanner =  Scanner(source);
    std::list<Token> tokens = scanner.scanTokens();

    for(auto token : tokens) {
        std::cout << token.toString() << std::endl;
    }
}

void runFile(std::string& fileName) {
    run(fileName);
}
void runPrompt() {

}

int main(int argc,char* argv[] ) {

    if(argc > 2) {
        std::cout << "Usage [GuigoLang]" << std::endl;
        exit(64);
    }
    if(argc == 2) {
        std::ifstream arquive(argv[1]);

        if(!arquive.is_open()) {
            std::cout << "Error opening file" << std::endl;
            return -1;
        }
        std::string line;
        std::string source;
        while(std::getline(arquive,line)) {
            source.append(line + "\n");
        }
        arquive.close();
        runFile(source);
    }else {
        runPrompt();
    }
    return 0;
}
