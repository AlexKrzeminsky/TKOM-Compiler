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

private:
    Var& var;
    std::unique_ptr<Expression> expr;
};

}

#endif