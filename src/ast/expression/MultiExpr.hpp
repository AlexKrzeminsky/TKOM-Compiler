#ifndef AST_MULTIEXPRESSION_HPP
#define AST_MULTIEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include "BaseMathExpr.hpp"
#include <list>

using namespace scanner;

namespace ast
{

class MultiExpr : public Expression
{
public:
    MultiExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }


    MultiExpr(MultiExpr &&rval) 
        : exprs(std::move(rval.exprs)),
          multiOps(std::move(rval.multiOps)) {}

    void addMultiply(exprPtr expr) {
        exprs.push_back(std::move(expr));
        multiOps.push_back(TokenType::T_Asterisk);
    }
    void addDivide(exprPtr expr) {
        exprs.push_back(std::move(expr));
        multiOps.push_back(TokenType::T_Slash);
    }

    virtual Var calculate() const {
        auto itExpr = exprs.begin();
        Var var = itExpr->get()->calculate();

        for (auto &&op : multiOps) {

            ++itExpr;
            if (op == TokenType::T_Asterisk)
                var = var * itExpr->get()->calculate();
            else if (op == TokenType::T_Slash)
                var = var / itExpr->get()->calculate();
            else
                throw std::runtime_error("Bad TokenType in multiplicativeOps");
        }

        return var;
    }

private:
    std::list<exprPtr> exprs;
    std::list<TokenType> multiOps;
};

}

#endif