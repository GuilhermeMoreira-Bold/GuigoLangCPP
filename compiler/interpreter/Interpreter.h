//
// Created by guilherme on 21/10/24.
//
#include <iostream>

#include "InterpretedData.h"
#include "../expressions/BinaryExpression.h"
#include "../expressions/ExpressionVisitor.h"
#include "../expressions/GroupExpression.h"
#include "../expressions/LiteralExpression.h"
#include "../expressions/UnaryExpression.h"
#include "../lexer/TokenType.h"
#include "../parser/ParsedData.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

template <typename T>
using Ref = std::shared_ptr<T>;

class Interpreter : public ExpressionVisitor, public CompilationPass<ParsedData, InterpretedData> {
public:
    const std::type_info& getInputType() override;

    const std::type_info& getOutputType() override;

    std::string getDebugName() override;

    InterpretedData* pass(ParsedData* input) override;

    void interpret(Ref<Expression> expression) {
        try {
            Object* value = evaluate(expression);
            std::cout << value->toString() << "\n";

        }catch (std::exception& e) {
            std::cout << e.what() << "\n";
            exit(1);
        }
    }

    Object* visitBinaryExpression(BinaryExpression& expression) override {
        Object* left = evaluate(expression.leftExpression);
        Object* right = evaluate(expression.rightExpression);
        switch (expression.op.token) {
            case Minus:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) - static_cast<double>(*right));
            case Slash:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) / static_cast<double>(*right));
            case Star:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) * static_cast<double>(*right));
            case Plus:
                if (left->getType() == Object::NUMBER && right->getType() == Object::NUMBER) {
                    return new Object(static_cast<double>(*left) + static_cast<double>(*right));
                }
                if (left->getType() == Object::STRING && right->getType() == Object::STRING) {
                    return new Object(*static_cast<std::string *>(left->getValue()) + *static_cast<std::string *>(right->getValue()));
                }
            throw new std::runtime_error("Operand must be two numbers or two strings" + std::to_string(expression.op.token) + " at:" +std::to_string(expression.op.line));
            case Greater:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) > static_cast<double>(*right));
            case Less:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) < static_cast<double>(*right));
            case GreaterEqual:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) >= static_cast<double>(*right));
            case LessEqual:
                checkNumberOperands(expression.op, left,right);
                return new Object(static_cast<double>(*left) <= static_cast<double>(*right));
            case EqualEqual:
                switch(left->getType()) {
                    case Object::NUMBER:
                        return new Object(static_cast<double>(*left) == static_cast<double>(*right));
                    case Object::STRING:
                        return new Object(*static_cast<std::string *>(left->getValue()) == *static_cast<std::string *>(right->getValue()));
                    case Object::BOOLEAN:
                        return new Object(*(bool*)left->getValue() == *(bool*)right->getValue());
                    default:
                        return new Object();
                }


            case Bang:
                return new Object(!isTruthy(right));
            case BangEqual:
                return new Object(!isEqual(left, right));
            default: ;
        }
        //Unrachable
        return nullptr;
    }
    bool isEqual(Object* left, Object* right) {
        if (left == nullptr && right == nullptr) return true;
        if (left == nullptr) return false;
        return left == right;
    }

    Object* visitUnaryExpression(UnaryExpression& expression) override {
        Object* right = evaluate(expression.expression);

        switch (expression.token.token) {
            case Minus:
                checkNumberOperand(expression.token, right);
            return new Object(-*right);
            case Bang:
                return new Object(!isTruthy(right));
            default:;
        }
        // Unreachable
        return nullptr;
    }

    bool isTruthy(Object* obj) {
        if (obj == nullptr) return false;
        if (obj->getType() == Object::BOOLEAN) {
            return *(bool*)obj->getValue();
        };
        return true;
    }

    Object* visitLiteralExpression(LiteralExpression& expression) override {
       return expression.obj;
    }

    Object*  visitGroupExpression(GroupExpression& expression) override {
        return evaluate(expression.expression);
    }

    Object* evaluate(Ref<Expression>expression) {
        return expression->accept(*this);
    }
    void checkNumberOperands(Token& op, Object* left, Object* right) {
        if (left->getType() == Object::NUMBER && right->getType() == Object::NUMBER) return;
        throw new std::runtime_error("Operand must be a numbers" + std::to_string(op.token) + " at:" +std::to_string(op.line));

    }

    void checkNumberOperand(Token& op, Object* operand) {
        if (operand->getType() == Object::NUMBER) return;
        throw new std::runtime_error("Operand must be a number" + std::to_string(op.token) + " at:" +std::to_string(op.line));
    }
    private:
        std::vector<Ref<Expression>> expressions;
};

inline const std::type_info & Interpreter::getInputType() {
    return typeid(ParsedData);
}

inline const std::type_info & Interpreter::getOutputType() {
    return typeid(InterpretedData);
}

inline std::string Interpreter::getDebugName() {
  return "Interpreter";
}

inline InterpretedData * Interpreter::pass(ParsedData* input) {
    expressions = input->getExpressions();
    interpret(expressions[0]);
}
#endif //INTERPRETER_H
