#ifndef AST_ANDEXPRESSION_HPP
#define AST_ANDEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "BaseLogicExpr.hpp"
#include <list>

namespace ast
{

class AndExpr : public Expression
{
public:
    AndExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    AndExpr(AndExpr&& rval) : exprs(std::move(rval.exprs)) {}

    void addAnd(exprPtr expr) {
        exprs.push_back(std::move(expr));
    }

    virtual Var calculate() const {
        Var var = exprs.begin()->get()->calculate();

        for(auto it = ++exprs.begin(); it!=exprs.end(); ++it) {
            var = var && it->get()->calculate();
            if (!var)
                break;
        }

        return var;
    }

private:
    std::list<exprPtr> exprs;
};

}

#endif