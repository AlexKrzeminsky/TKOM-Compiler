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

    Return run() override {
        Return ret;
        unsigned int maxLoops = 1000000;

        while (expr->calculate() && --maxLoops > 0) {
            ret = whileBlock->run();

            switch (ret.type) {
                case Return::Break:
                    return Return(Return::None);

                case Return::Variable:
                    return ret;

                default:
                    continue;
            }
        }
        if (maxLoops <= 0)
            throw std::runtime_error("Time out in WhileStatement");
        else {
            return Return(Return::None);
        }
    }

private:
    std::unique_ptr<Expression> expr; 
    stmtBlockPtr whileBlock;
};

}

#endif