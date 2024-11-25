//
// Created by guilherme on 14/10/24.
//

#ifndef PARSER_H
#define PARSER_H
#include <vector>

#include "ParsedData.h"
#include "../lexer/Token.h"
#include "../expressions/Expression.h"
#include "../pass/CompilationPass.h"
#include "../scanner/ScannedData.h"

template <typename T>
using Ref = std::shared_ptr<T>;

class Parser : public CompilationPass<ScannedData, ParsedData> {
public:

    void resetInternalState(ScannedData* input);
    Parser() = default;
    ParsedData* pass(ScannedData* input);
    Ref<Expression> parse() {
        return expression();
    }

    const std::type_info & getInputType() override;

    const std::type_info & getOutputType() override;

    std::string getDebugName() override;

private:
    void synchronize();

    int current = 0;
    std::vector<Ref<Token>>* tokens;
    std::vector<Ref<Expression>> expressions;

    template<typename ...Args>
    bool match(Args... types);
    bool check(TOKENTYPE type);
    bool isAtEnd();
    void scanExpressions();
    Ref<Token> consume(TOKENTYPE type, std::string message);
    Ref<Token> advance();
    Ref<Token> peek();
    Ref<Token> previous();

    Ref<Expression> expression();
    Ref<Expression> equality();
    Ref<Expression> comparison();
    Ref<Expression> term();
    Ref<Expression> factor();
    Ref<Expression> unary();
    Ref<Expression> literal();
};
#endif //PARSER_H
