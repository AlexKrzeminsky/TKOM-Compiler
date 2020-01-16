#ifndef AST_OREXPRESSION_HPP
#define AST_OREXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "AndExpr.hpp"
#include <list>

namespace ast
{

class OrExpr : public Expression
{
public:
    OrExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    OrExpr(OrExpr &&rval)
        : exprs(std::move(rval.exprs)) {}

    void addOr(exprPtr expr) {
        exprs.push_back(std::move(expr));
    }

    virtual Var calculate() const {
        Var var = exprs.begin()->get()->calculate();

        for(auto it = ++exprs.begin(); it!=exprs.end(); ++it) {
            var = var || it->get()->calculate();
            if (var)
                break;
        }

        return var;
    }

private:
    std::list<exprPtr> exprs;
};

}

#endif