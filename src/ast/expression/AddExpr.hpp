#ifndef AST_ADDXPRESSION_HPP
#define AST_ADDXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include "MultiExpr.hpp"
#include <vector>

using namespace scanner;

namespace ast
{

class AddExpr : public Expression
{
public:
    AddExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    void addPlus(exprPtr expr) {
        exprs.push_back(std::move(expr));
        addOps.push_back(TokenType::T_Plus);
    }
    void addMinus(exprPtr expr) {
        exprs.push_back(std::move(expr));
        addOps.push_back(TokenType::T_Minus);
    }

    void print() {
        std::cout << "\nAddExpr:\n";
        exprs[0]->print();
        for (unsigned int i = 0; i < addOps.size(); i++) {
            exprs[i+1]->print();
            if (addOps[i] == TokenType::T_Plus) std::cout << " + ";
            else if (addOps[i] == TokenType::T_Minus) std::cout << " - ";
        }
    }

private:
    std::vector<exprPtr> exprs;
    std::vector<TokenType> addOps;
};

}

#endif