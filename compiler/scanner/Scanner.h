//
// Created by guilherme on 07/10/24.
//
#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include <unordered_map>
#include "ScannedData.h"
#include "../file/GuigoFile.h"
#include "../lexer/Token.h"
#include "../pass/CompilationPass.h"

template <typename T>
using Ref = std::shared_ptr<T>;

class Scanner : public CompilationPass<GuigoFile,ScannedData> {
public:
    const std::type_info &getInputType() override;
    const std::type_info &getOutputType() override;

    std::string getDebugName() override;
    void resetInternalState(GuigoFile* input);
    ScannedData* pass(GuigoFile* input) override;

    std::string source;
    std::vector<Ref<Token>> tokens;

    void scanTokens();
    bool isAtEnd();

    void string();

    char peekNext();

    void number();
    std::unordered_map<std::string, TOKENTYPE> keywords;
    bool isAlphaNumeric(char peek);

    void identifier();

    void scanToken();
    char advance();
    void addToken(TOKENTYPE token);
    void addToken(TOKENTYPE token, Object* literal);
    bool match(char expected);
    char peek();
    Scanner();
private:
    int start = 0;
    int current = 0;
    int line = 1;
};



#endif //SCANNER_H
