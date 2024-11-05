//
// Created by guilherme on 21/10/24.
//

#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

class Expression;
class ExpressionVisitor;
class Token;

class UnaryExpression : public Expression {
    public:
    UnaryExpression(Expression* e, Token &t) : expression(e), token(t) {};

    virtual ~UnaryExpression() override = default;

    std::string toString() override {
        return "UnaryExpression:  " + expression->toString() + "(" + token.toString() + ")";
    };
    Object* accept(ExpressionVisitor &visitor) override {
        visitor.visitUnaryExpression(*this);
    };

    Token& token;
    Expression* expression;

};
#endif //UNARYEXPRESSION_H
