#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include <memory>
#include "../Var.hpp"

namespace ast
{


class Expression
{
public:
    virtual ~Expression() = default;
    virtual Var calculate() const = 0;
};
using exprPtr = std::unique_ptr<Expression>;

}

#endif