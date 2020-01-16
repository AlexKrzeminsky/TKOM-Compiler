#ifndef AST_BASEMATHEXPRESSION_HPP
#define AST_BASEMATHEXPRESSION_HPP

#include "Expression.hpp"
#include <iostream>

namespace ast
{

class BaseMathExpr : public Expression
{
public:
    BaseMathExpr() = delete;
    BaseMathExpr(Var* literal_, bool unary_ = false) : literal(literal_), unary(unary_) {}

    BaseMathExpr(Var& variable_, bool unary_)
        : variable(&variable_), unary(unary_) {}

    BaseMathExpr(std::unique_ptr<Statement> funCall_, bool unary_)
        : unary(unary_), funCall(std::move(funCall_)) {}

    BaseMathExpr(Var& variable_, std::unique_ptr<Expression> index_, bool unary_ = false) : 
        variable(&variable_), unary(unary_), index(std::move(index_)) {}

    BaseMathExpr(Var& variable_, std::unique_ptr<Expression> sIdx1_, std::unique_ptr<Expression> sIdx2_, bool unary_ = false) : 
        variable(&variable_), unary(unary_), sIdx1(std::move(sIdx1_)), sIdx2(std::move(sIdx2_)) {}


    BaseMathExpr(std::unique_ptr<Expression> expr_, bool unary_)
        : unary(unary_), parentLogicExpr(std::move(expr_)) {}

    BaseMathExpr(BaseMathExpr &&rval)
        : literal(rval.literal),
          variable(rval.variable),
          unary(rval.unary),
          funCall(std::move(rval.funCall)),
          parentLogicExpr(std::move(rval.parentLogicExpr)) {

        rval.unary = false;
        rval.literal = nullptr;
    }

    ~BaseMathExpr() { delete literal; }

    virtual Var calculate() const {
        Var currVar;
        if (literal) {
            currVar = *literal;
        } else if (variable) {
            if (index != nullptr) {
                int idx = index->calculate().value[0];
                currVar = Var(VarType::INT, valueVec({variable->at(static_cast<unsigned int>(idx))}));
            }
            else if (sIdx1 != nullptr) {
                if (sIdx2 != nullptr) {
                    int idx1 = sIdx1->calculate().value[0];
                    int idx2 = sIdx2->calculate().value[0];
                    valueVec tmp;
                    for ( int i = idx1; i < idx2; ++i)
                        tmp.push_back(variable->at(static_cast<unsigned int>(i)));
                    currVar = Var(VarType::INT, tmp);
                }
            } else {
                currVar = *variable;
            }
        } else if (funCall != nullptr) {
            currVar = funCall->run().variable;
        } else if (parentLogicExpr != nullptr) {
            currVar = parentLogicExpr->calculate();
        }

        if (unary) {
            currVar = -currVar;
        }
        return currVar;
    }

private:
    Var* literal = nullptr;
    Var* variable = nullptr;
    bool unary;
    std::unique_ptr<Expression> index;
    std::unique_ptr<Expression> sIdx1;
    std::unique_ptr<Expression> sIdx2;

    std::unique_ptr<Statement> funCall;
    std::unique_ptr<Expression> parentLogicExpr;
};

}

#endif