#ifndef AST_BASELOGICEXPRESSION_HPP
#define AST_BASELOGICEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "AddExpr.hpp"
#include <list>

namespace ast
{

class BaseLogicExpr : public Expression
{
public:
    BaseLogicExpr(exprPtr expr_, bool unary_ = false) 
    : unary(unary_) {
        exprs.push_back(std::move(expr_));
    }

    BaseLogicExpr(BaseLogicExpr &&rval) 
    : exprs(std::move(rval.exprs)), unary(rval.unary) {} 

    virtual Var calculate() const {
        return unary ? !exprs.begin()->get()->calculate() : exprs.begin()->get()->calculate();
    }
    
private:
    std::list<exprPtr> exprs;
    bool unary;
};

}

#endif