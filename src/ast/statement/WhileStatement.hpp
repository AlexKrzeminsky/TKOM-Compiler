#ifndef PARSER_WHILESTATEMENT_HPP_
#define PARSER_WHILESTATEMENT_HPP_

#include "Statement.hpp"
#include "BlockStatement.hpp"

namespace ast
{

using stmtBlockPtr = std::unique_ptr<BlockStatement>;

class WhileStatement : public Statement
{
public:
    WhileStatement (std::unique_ptr<Expression> expr_, stmtBlockPtr whileBlock_) 
    : expr(std::move(expr_)), whileBlock(std::move(whileBlock_)) {}

private:
    std::unique_ptr<Expression> expr; 
    stmtBlockPtr whileBlock;
};

}

#endif