#ifndef PARSER_RETURNSTATEMENT_HPP_
#define PARSER_RETURNSTATEMENT_HPP_

#include <memory>
#include "Statement.hpp"
#include "../expression/Expression.hpp"

namespace ast {

class ReturnStatement : public Statement {
public:
    explicit ReturnStatement(std::unique_ptr<Expression> expression)
            : expression(std::move(expression)) {
    }

private:
    std::unique_ptr<Expression> expression;
};

}

#endif