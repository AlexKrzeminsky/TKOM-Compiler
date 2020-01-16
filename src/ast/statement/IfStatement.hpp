#ifndef PARSER_IFSTATEMENT_HPP_
#define PARSER_IFSTATEMENT_HPP_

#include "Statement.hpp"
#include "BlockStatement.hpp"
#include "../expression/Expression.hpp"

namespace ast
{

using stmtBlockPtr = std::unique_ptr<BlockStatement>;

class IfStatement : public Statement
{
public:
    IfStatement (std::unique_ptr<Expression> expr_, stmtBlockPtr ifBlock_) 
        : expr(std::move(expr_)), ifBlock(std::move(ifBlock_)) {}

    IfStatement (std::unique_ptr<Expression> expr_, stmtBlockPtr ifBlock_, stmtBlockPtr elseBlock_) 
        : IfStatement(std::move(expr_), std::move(ifBlock_)) {
        elseBlock = std::move(elseBlock_);
    }

    Return run() override {
        if (expr->calculate()) {
            return ifBlock->run();
        } else {
            if (elseBlock != nullptr) {
                return elseBlock->run();
            } else {
                return Return(Return::None);
            }
        }
    }

private:
    std::unique_ptr<Expression> expr;
    stmtBlockPtr ifBlock;
    stmtBlockPtr elseBlock;
};

}

#endif