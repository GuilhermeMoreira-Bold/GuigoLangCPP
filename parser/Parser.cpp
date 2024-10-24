//
// Created by guilherme on 14/10/24.
//

#include "Parser.h"


#include "../expressions/BinaryExpression.h"
#include "../expressions/UnaryExpression.h"
#include "../expressions/LiteralExpression.h"
#include "../expressions/GroupExpression.h"
#include "../error/GuigoErrorCode.h"
#include "../error/GuigoError.h"


Expression* Parser::expression() {
    return equality();
}

Expression* Parser::equality() {
    Expression* expr = comparison();

    if (match(BangEqual, EqualEqual)) {
        Token& op = previous();
        Expression* right = comparison();
        expr = new BinaryExpression(expr,  right, op);
    }
    return expr;
}

Expression* Parser::comparison() {
    Expression* expr = term();

    if (match(Greater, GreaterEqual, Less,LessEqual)) {
        Token& op = previous();
        Expression* right = term();
        expr = new BinaryExpression(expr,  right, op);
    }
    return expr;
}

Expression *Parser::term() {
    Expression* expr = factor();
    while (match(Minus,Plus)) {
        Token& op = previous();
        Expression* right = factor();
        expr = new BinaryExpression(expr,  right, op);
    }
    return expr;
}


Expression *Parser::factor() {
    Expression* expr = unary();
    while (match(Slash,Star)) {
        Token& op = previous();
        Expression* right = unary();
        expr = new BinaryExpression(expr,  right, op);
    }
    return expr;
}

Expression* Parser::unary() {
    if (match(Bang, Minus)) {
        Token& op = previous();
        Expression* right = unary();
        return new UnaryExpression(right, op);
    }
    return literal();
}


Expression *Parser::literal() {
    if (match(False)) return new LiteralExpression(new Object(false));
    if (match(True)) return new LiteralExpression(new Object(true));
    if (match(Number,String)) {
        return new LiteralExpression(previous().literal);
    }

    if (match(LeftParent)) {
        Expression* expr = expression();
        consume(RightParent, "Expect ')' after expression.");
        return new GroupExpression(expr);
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
    return peek().token == type;
}

Token &Parser::advance() {
    if (!isAtEnd()) current ++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().token == Eof;
}

Token& Parser::peek() {
    auto it = tokens.begin();
    std::advance(it, current);
    return *it;
}

Token& Parser::previous() {
    auto it = tokens.begin();
    std::advance(it, current -1);
    return *it;
}

Token &Parser::consume(TOKENTYPE type, std::string message) {
    if (check(type)) return advance();
    GuigoError::parserError(message, GuigoErrorCode::InvalidExpression);
};

void Parser::synchronize(){
    advance();
    while (!isAtEnd()) {
        if (previous().token == Semicolon) return;

        switch (peek().token) {
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
