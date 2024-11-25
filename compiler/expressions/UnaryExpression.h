//
// Created by guilherme on 21/10/24.
//

#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

class Expression;
class ExpressionVisitor;
class Token;


template <typename T>
using Ref = std::shared_ptr<T>;

class UnaryExpression : public Expression {
    public:
    UnaryExpression(Ref<Expression> e, Token &t) : expression(e), token(t) {};

    ~UnaryExpression() override = default;

    std::string toString() override {
        return "UnaryExpression:  " + expression->toString() + "(" + token.toString() + ")";
    };
    Object* accept(ExpressionVisitor &visitor) override {
        visitor.visitUnaryExpression(*this);
    };

    Token& token;
    Ref<Expression> expression;

};
#endif //UNARYEXPRESSION_H
