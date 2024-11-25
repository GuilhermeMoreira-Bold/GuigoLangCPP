//
// Created by guilherme on 14/10/24.
//

#include "Parser.h"

#include <vector>


#include "../expressions/BinaryExpression.h"
#include "../expressions/UnaryExpression.h"
#include "../expressions/LiteralExpression.h"
#include "../expressions/GroupExpression.h"
#include "../error/GuigoErrorCode.h"
#include "../error/GuigoError.h"

void Parser::resetInternalState(ScannedData* input) {
    tokens = &input->getTokens();
}

ParsedData* Parser::pass(ScannedData* input) {
    resetInternalState(input);
    scanExpressions();

    for(auto& expression : expressions) {
        std::cout << expression->toString() << std::endl;
    }

    return new ParsedData(expressions);
}

const std::type_info & Parser::getInputType() {
    return typeid(ScannedData);
}

const std::type_info & Parser::getOutputType() {
    return typeid(ParsedData);
}

std::string Parser::getDebugName() {
    return "Parser";
}

void Parser::scanExpressions() {
    while(!isAtEnd()) {
        expressions.push_back(expression());
    }
}


Ref<Expression> Parser::expression() {
    return equality();
}

Ref<Expression> Parser::equality() {
    Ref<Expression> expr = comparison();

    if (match(BangEqual, EqualEqual)) {
        Ref<Token> op = previous();
        Ref<Expression> right = comparison();
        expr = std::make_shared<BinaryExpression>(expr,  right, *op);
    }
    return expr;
}

Ref<Expression> Parser::comparison() {
    Ref<Expression> expr = term();

    if (match(Greater, GreaterEqual, Less,LessEqual)) {
        Ref<Token> op = previous();
        Ref<Expression> right = term();
        expr = std::make_shared<BinaryExpression>(expr,  right, *op);
    }
    return expr;
}

Ref<Expression>Parser::term() {
    Ref<Expression> expr = factor();
    while (match(Minus,Plus)) {
        Ref<Token> op = previous();
        Ref<Expression> right = factor();
        expr = std::make_shared<BinaryExpression>(expr,  right, *op);
    }
    return expr;
}


Ref<Expression>Parser::factor() {
    Ref<Expression> expr = unary();
    while (match(Slash,Star)) {
        Ref<Token> op = previous();
        Ref<Expression> right = unary();
        expr = std::make_shared<BinaryExpression>(expr,  right, *op);
    }
    return expr;
}

Ref<Expression> Parser::unary() {
    if (match(Bang, Minus)) {
        Ref<Token> op = previous();
        Ref<Expression> right = unary();
        return std::make_shared<UnaryExpression>(right, *op);
    }
    return literal();
}


Ref<Expression>Parser::literal() {
    if (match(False)) return std::make_shared<LiteralExpression>(new Object(false));
    if (match(True)) return std::make_shared<LiteralExpression>(new Object(true));
    if (match(Number,String)) {
        return std::make_shared<LiteralExpression>(previous()->literal);
    }

    if (match(LeftParent)) {
        Ref<Expression> expr = expression();
        consume(RightParent, "Expect ')' after expression.");
        return std::make_shared<GroupExpression>(expr);
    }
    //unrechable
    GuigoError::parserError("Invalid expression.", GuigoErrorCode::InvalidExpression);
    exit(64);
    return nullptr;
}

template <typename ...Args>
bool Parser::match(Args... types) {
    for (auto type: {types...}) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TOKENTYPE type) {
    if (isAtEnd()) return false;
    return peek()->token == type;
}

Ref<Token> Parser::advance() {
    if (!isAtEnd()) current ++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek()->token == Eof;
}

Ref<Token> Parser::peek() {
    auto it = tokens->begin();
    std::advance(it, current);
    return *it;
}

Ref<Token> Parser::previous() {
    auto it = tokens->begin();
    std::advance(it, current -1);
    return *it;
}

Ref<Token> Parser::consume(TOKENTYPE type, std::string message) {
    if (check(type)) return advance();
    GuigoError::parserError(message, GuigoErrorCode::InvalidExpression);
};

void Parser::synchronize(){
    advance();
    while (!isAtEnd()) {
        if (previous()->token == Semicolon) return;

        switch (peek()->token) {
            case Class:
                case Var:
            case If:
            case While:
            case Print:
            case Return:
            return;
        }
        advance();
    }
}
