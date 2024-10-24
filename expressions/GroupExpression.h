//
// Created by guilherme on 21/10/24.
//

#ifndef GROUPEXPRESSION_H
#define GROUPEXPRESSION_H

#include <memory>

#include "Expression.h"
#include "ExpressionVisitor.h"

class Token;

class GroupExpression : public Expression{
    public:
    GroupExpression(Expression* expression) : expression(std::move(expression)){};
    Object* accept(ExpressionVisitor& visitor) override{
        visitor.visitGroupExpression(*this);
    };
    std::string toString() override {
        return "GroupExpression" + expression->toString();
    };
    Expression* expression;
};
#endif //GROUPEXPRESSION_H
