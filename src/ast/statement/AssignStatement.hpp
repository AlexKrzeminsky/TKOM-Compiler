#ifndef PARSER_ASSIGNSTATEMENT_HPP_
#define PARSER_ASSIGNSTATEMENT_HPP_

#include "Statement.hpp"
#include "../expression/Expression.hpp"
#include "../Var.hpp"

namespace ast
{

class AssignStatement : public Statement
{
public:
    AssignStatement(Var &var_, std::unique_ptr<Expression> expr_) :
        var(var_), expr(std::move(expr_)) {}

    AssignStatement(Var &var_, std::unique_ptr<Expression> index_, std::unique_ptr<Expression> expr_) : 
        var(var_), expr(std::move(expr_)), index(std::move(index_)) {
    }

    Return run() override {
        Var ret = expr->calculate();
        if (index != nullptr) {
            Var idx = index->calculate();
            if (idx.value[0] >= 0) {
                if (ret.size() == 1) {
                    var.at(static_cast<unsigned int>(idx.value[0])) = ret.at(0);
                } else {
                    throw std::runtime_error("Cannot assign vector to int");
                }
            }
        } else {
            var = ret;
        }

        return Return(Return::None);
    }

private:
    Var& var;
    std::unique_ptr<Expression> expr;
    std::unique_ptr<Expression> index;
};

}

#endif