#ifndef AST_EXPRESSION_HPP
#define AST_EXPRESSION_HPP

#include <memory>

namespace ast
{


class Expression
{
public:
    virtual ~Expression() = default;
    virtual void print() {}
};
using exprPtr = std::unique_ptr<Expression>;

}

#endif