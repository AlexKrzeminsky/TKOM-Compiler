#ifndef AST_MULTIEXPRESSION_HPP
#define AST_MULTIEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include "BaseMathExpr.hpp"
#include <vector>

using namespace scanner;

namespace ast
{

class MultiExpr : public Expression
{
public:
    MultiExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    void addMultiply(exprPtr expr) {
        exprs.push_back(std::move(expr));
        multiOps.push_back(TokenType::T_Asterisk);
    }
    void addDivide(exprPtr expr) {
        exprs.push_back(std::move(expr));
        multiOps.push_back(TokenType::T_Slash);
    }

    void print() {
        std::cout << "\nMultiExpr:\n";
        exprs[0]->print();
        for (unsigned int i = 0; i < multiOps.size(); i++) {
            exprs[i+1]->print();
            if (multiOps[i] == TokenType::T_Asterisk) std::cout << " * ";
            else if (multiOps[i] == TokenType::T_Slash) std::cout << " / ";
        }
    }

private:
    std::vector<exprPtr> exprs;
    std::vector<TokenType> multiOps;
};

}

#endif