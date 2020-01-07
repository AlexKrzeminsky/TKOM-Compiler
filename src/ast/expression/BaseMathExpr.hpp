#ifndef AST_BASEMATHEXPRESSION_HPP
#define AST_BASEMATHEXPRESSION_HPP

#include "Expression.hpp"
#include <iostream>

namespace ast
{

class BaseMathExpr : public Expression
{
public:
    BaseMathExpr(Var* variable_, bool unary_ = false) : variable(variable_), unary(unary_) {}

    BaseMathExpr(Var &variable_, bool unary_)
        : variable(&variable_), unary(unary_){}

    BaseMathExpr(std::unique_ptr<Statement> funCall_, bool unary_)
        : unary(unary_), funCall(std::move(funCall_)) {}

    
    BaseMathExpr(Var variable_, unsigned int index_, bool unary_ = false) : 
        variable(&variable_), unary(unary_), index(index_){}

    BaseMathExpr(std::unique_ptr<Expression> expr_, bool unary_)
        : unary(unary_), parentLogicExpr(std::move(expr_)) {}

    void print() {
        std::cout << "\nBaseMathExpr:\n";
        variable->print();
    }

private:
    Var* variable;
    bool unary;
    int index = -1;

    std::unique_ptr<Statement> funCall;
    std::unique_ptr<Expression> parentLogicExpr;
};

}

#endif