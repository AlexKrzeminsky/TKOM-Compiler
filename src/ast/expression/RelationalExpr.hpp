#ifndef AST_RELATIONEXPRESSION_HPP
#define AST_RELATIONEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include <vector>

using namespace scanner;

namespace ast
{
class RelationExpr : public Expression
{
public:
    RelationExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    void addEqual(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_Equal2);
    }
    void addNotEqual(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_NotEqual);
    }
    void addLessThan(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_LessThan);
    }
    void addLessEqual(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_LeEqThan);
    }
    void addGreaterThan(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_GreaterThan);
    }
    void addGreaterEqual(exprPtr expr) {
        exprs.push_back(std::move(expr));
        relationOps.push_back(TokenType::T_GrEqThan);
    }

    void print() {
        exprs[0]->print();
        for (unsigned int i = 0; i < relationOps.size(); i++) {
            exprs[i+1]->print();
            if (relationOps[i] == TokenType::T_Equal2) std::cout << " == ";
            else if (relationOps[i] == TokenType::T_NotEqual) std::cout << " != ";
            else std::cout << " rest ";
        }
    }

private:
    std::vector<exprPtr> exprs;
    std::vector<TokenType> relationOps;
};

}

#endif