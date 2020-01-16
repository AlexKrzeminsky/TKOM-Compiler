#ifndef AST_RELATIONEXPRESSION_HPP
#define AST_RELATIONEXPRESSION_HPP

#include "Expression.hpp"
#include "../Var.hpp"
#include "../../scanner/TokenType.hpp"
#include <list>

using namespace scanner;

namespace ast
{
class RelationExpr : public Expression
{
public:
    RelationExpr(exprPtr expr_) {
        exprs.push_back(std::move(expr_));
    }

    RelationExpr(RelationExpr &&rhs)
        : exprs(std::move(rhs.exprs)),
          relationOps(std::move(rhs.relationOps)) {}

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

    virtual Var calculate() const {
        auto itExpr = exprs.begin();
        Var var = itExpr->get()->calculate();

        for (auto &&op : relationOps) {
            ++itExpr;
            if (op == TokenType::T_Equal2)
                var = var == itExpr->get()->calculate();
            else if (op == TokenType::T_NotEqual)
                var = var != itExpr->get()->calculate();
            else if (op == TokenType::T_LessThan)
                var = var < itExpr->get()->calculate();
            else if (op == TokenType::T_LeEqThan)
                var = var <= itExpr->get()->calculate();
            else if (op == TokenType::T_GreaterThan)
                var = var > itExpr->get()->calculate();
            else if (op == TokenType::T_GrEqThan)
                var = var >= itExpr->get()->calculate();
            else
                throw std::runtime_error("Bad TokenType in relationOps");
        }

        return var;
    }

private:
    std::list<exprPtr> exprs;
    std::list<TokenType> relationOps;
};

}

#endif