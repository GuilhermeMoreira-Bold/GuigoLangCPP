//
// Created by guilherme on 14/10/24.
//

#ifndef EXPRESSIONVISITOR_H
#define EXPRESSIONVISITOR_H


class GroupExpression;
class LiteralExpression;
class UnaryExpression;
class BinaryExpression;

class ExpressionVisitor {
public:
    virtual ~ExpressionVisitor() = default;

    virtual Object* visitBinaryExpression(BinaryExpression &expression) = 0;
    virtual Object* visitUnaryExpression(UnaryExpression &expression) = 0;
    virtual Object* visitLiteralExpression(LiteralExpression &expression) = 0;
    virtual Object* visitGroupExpression(GroupExpression& expression) = 0;
};

#endif //EXPRESSIONVISITOR_H
