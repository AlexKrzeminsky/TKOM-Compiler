#ifndef AST_ADDXPRESSION_HPP
#define AST_ADDXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include "MultiExpr.hpp"
#include <list>

using namespace scanner;

namespace ast
{

class AddExpr : public Expression
{
public:
    AddExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    AddExpr(AddExpr &&rval) 
        : exprs(std::move(rval.exprs)),
          addOps(std::move(rval.addOps)) {}

    void addPlus(exprPtr expr) {
        exprs.push_back(std::move(expr));
        addOps.push_back(TokenType::T_Plus);
    }

    void addMinus(exprPtr expr) {
        exprs.push_back(std::move(expr));
        addOps.push_back(TokenType::T_Minus);
    }

    virtual Var calculate() const {
        auto itExpr = exprs.begin();
        Var var = itExpr->get()->calculate();

        for (auto &&op : addOps) {
            ++itExpr;
            if (op == TokenType::T_Plus)
                var = var + itExpr->get()->calculate();
            else if (op == TokenType::T_Minus)
                var = var - itExpr->get()->calculate();
            else
                throw std::runtime_error("Bad TokenType in additiveOps");
        }

        return var;
    }

private:
    std::list<exprPtr> exprs;
    std::list<TokenType> addOps;
};

}

#endif