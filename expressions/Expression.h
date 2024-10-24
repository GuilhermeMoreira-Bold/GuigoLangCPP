//
// Created by guilherme on 14/10/24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
class Object;
class Expression {
public:
    virtual ~Expression() = default;

    virtual Object* accept(class ExpressionVisitor& e) = 0;
    virtual std::string toString() = 0;

};
#endif //EXPRESSION_H
