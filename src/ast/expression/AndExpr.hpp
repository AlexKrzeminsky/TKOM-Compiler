#ifndef AST_ANDEXPRESSION_HPP
#define AST_ANDEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "BaseLogicExpr.hpp"
#include <vector>

namespace ast
{

class AndExpr : public Expression
{
public:
    AndExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    void addAnd(exprPtr expr) {
        exprs.push_back(std::move(expr));
    }

    void print() {
        std::cout << "\nAndExpr:\n";
        for (unsigned int i = 0; i < exprs.size(); i++) {
            exprs[i]->print();
        }
    }

private:
    std::vector<exprPtr> exprs;
};

}

#endif