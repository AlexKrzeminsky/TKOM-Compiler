#ifndef AST_OREXPRESSION_HPP
#define AST_OREXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "AndExpr.hpp"
#include <vector>

namespace ast
{

class OrExpr : public Expression
{
public:
    OrExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    void addOr(exprPtr expr) {
        exprs.push_back(std::move(expr));
    }

    void print() {
        std::cout << "\nOrExpr:\n";
        for (unsigned int i = 0; i < exprs.size(); i++) {
            exprs[i]->print();
        }
    }

private:
    std::vector<exprPtr> exprs;
};

}

#endif