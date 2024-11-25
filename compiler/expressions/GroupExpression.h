//
// Created by guilherme on 21/10/24.
//

#ifndef GROUPEXPRESSION_H
#define GROUPEXPRESSION_H

#include <memory>

#include "Expression.h"
#include "ExpressionVisitor.h"

class Token;

template <typename T>
using Ref = std::shared_ptr<T>;

class GroupExpression : public Expression{
    public:
    GroupExpression(Ref<Expression> expression) : expression(std::move(expression)){};
    Object* accept(ExpressionVisitor& visitor) override{
        visitor.visitGroupExpression(*this);
    };
    std::string toString() override {
        return "GroupExpression" + expression->toString();
    };
    Ref<Expression> expression;
};
#endif //GROUPEXPRESSION_H
