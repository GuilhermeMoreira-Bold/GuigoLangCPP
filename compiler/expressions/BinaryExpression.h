//
// Created by guilherme on 14/10/24.
//

#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../lexer/Token.h"


class BinaryExpression : public Expression {
    public:
    Expression* leftExpression;
    Expression* rightExpression;
    Token& op;
    BinaryExpression(Expression* leftExpression,Expression* rightExpression, Token &op) : leftExpression(leftExpression), rightExpression(rightExpression), op(op) {};
    Object* accept(ExpressionVisitor& visitor) override {
        visitor.visitBinaryExpression(*this);
    };
    std::string toString() {
        return "Binary Expression:( " + leftExpression->toString() + " " +  op.toString() + " " + rightExpression->toString() + ")";
    };

};



#endif //BINARYEXPRESSION_H
