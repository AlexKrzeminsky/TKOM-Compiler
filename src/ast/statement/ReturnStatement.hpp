#ifndef PARSER_RETURNSTATEMENT_HPP_
#define PARSER_RETURNSTATEMENT_HPP_

#include <memory>
#include "Statement.hpp"
#include "../expression/Expression.hpp"

namespace ast {

class ReturnStatement : public Statement {
public:
    explicit ReturnStatement(std::unique_ptr<Expression> expression)
            : expr(std::move(expression)) {
    }
    explicit ReturnStatement(Return::Type type)
            : return_(type) {}

    Return run() override {
        if(expr != nullptr) {
            return Return(Return::Variable, expr->calculate());
        } else {
            return Return(return_);
        }
    }

private:
    std::unique_ptr<Expression> expr;
    Return::Type return_ = Return::None;
};

}

#endif