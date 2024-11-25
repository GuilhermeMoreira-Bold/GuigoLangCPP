//
// Created by guilherme on 21/10/24.
//

#ifndef LITERALEXPRESSION_H
#define LITERALEXPRESSION_H
#include <memory>

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "ExpressionVisitor.h"
#include "../obj/Object.h"

class Token;
class ExpressionVisitor;

template <typename T>
using Ref = std::shared_ptr<T>;
class LiteralExpression : public Expression {
    public:
    LiteralExpression(Object* obj) : obj(std::move(obj)) {};
    virtual ~LiteralExpression() {};
    Object* accept(ExpressionVisitor &visitor) override {
        visitor.visitLiteralExpression(*this);
    };
    std::string toString() override {
        void* valuePtr = obj->getValue();
        std::string str = "LiteralExpression: ";
        switch (obj->getType()) {
            case Object::NUMBER:
                str += std::to_string(*((double*)valuePtr));
            break;
            case Object::STRING:
                str += *((std::string*)valuePtr);
            break;
            case Object::BOOLEAN:
                str += std::to_string(*(bool*)valuePtr);
            break;
            case Object::Null:
                str += "null";
            break;
        }
        return str;
    };
    Object* obj;
};
#endif //LITERALEXPRESSION_H
