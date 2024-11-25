#include <iostream>

#include "../../compiler/scanner/Scanner.h"
#include <fstream>
#include "../../compiler/pipeline/CompilationPipeline.h"
#include "../../compiler/interpreter/Interpreter.h"
#include "../../compiler/parser/Parser.h"


void run(std::string& source) {

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
        CompilationPipeline pipeline;
        GuigoFile* file = new GuigoFile(std::move(arquive));
        pipeline.insertStage(new Scanner);
        pipeline.insertStage(new Parser);
        pipeline.insertStage(new Interpreter);

        pipeline.execute(file);
    }else {
        runPrompt();
    }
    return 0;
}

