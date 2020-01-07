#ifndef AST_BASELOGICEXPRESSION_HPP
#define AST_BASELOGICEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "AddExpr.hpp"
#include <vector>

namespace ast
{

class BaseLogicExpr : public Expression
{
public:
    BaseLogicExpr(exprPtr expr_, bool unary_ = false) 
    : unary(unary_) {
        exprs.push_back(std::move(expr_));
    }

    void print() {
        std::cout << "\nBaseLogicExpr:\n";
        for (unsigned int i = 0; i < exprs.size(); i++) {
            exprs[i]->print();
        }
    }
    
private:
    std::vector<exprPtr> exprs;
    bool unary;
};

}

#endif