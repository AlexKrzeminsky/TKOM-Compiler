#ifndef AST_STATEMENT_HPP_
#define AST_STATEMENT_HPP_

#include <memory>
#include "../Return.hpp"

namespace ast
{

class Statement 
{
public:
    virtual ~Statement() = default;

    virtual Return run() { return Return(Return::None); }
};

}

#endif