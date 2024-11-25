//
// Created by guilherme on 14/10/24.
//

#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H
#include <memory>

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../lexer/Token.h"


template <typename T>
using Ref = std::shared_ptr<T>;
class BinaryExpression : public Expression {
    public:
    Ref<Expression> leftExpression;
    Ref<Expression> rightExpression;
    Token& op;
    BinaryExpression(Ref<Expression> leftExpression,Ref<Expression> rightExpression, Token &op) : leftExpression(leftExpression), rightExpression(rightExpression), op(op) {};
    Object* accept(ExpressionVisitor& visitor) override {
        visitor.visitBinaryExpression(*this);
    };
    std::string toString() {
        return "Binary Expression:( " + leftExpression->toString() + " " +  op.toString() + " " + rightExpression->toString() + ")";
    };

};



#endif //BINARYEXPRESSION_H
