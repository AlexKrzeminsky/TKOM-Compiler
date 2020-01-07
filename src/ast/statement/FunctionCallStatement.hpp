#ifndef PARSER_FUNCALLSTATEMENT_HPP_
#define PARSER_FUNCALLSTATEMENT_HPP_

#include <vector>
#include <memory>
#include "Statement.hpp"
#include "FunctionDefStatement.hpp"
#include "../expression/Expression.hpp"

namespace ast {

class FunctionCall : public Statement {
public:
    explicit FunctionCall(FunctionDefinition &functionDef)
            : functionDef(functionDef) {
    }

    void addExpression(std::unique_ptr<Expression> expr) {
        expressions.push_back(std::move(expr));
    }

    unsigned size() { return expressions.size(); }

private:
    FunctionDefinition &functionDef;
    std::vector<std::unique_ptr<Expression>> expressions;
};

}


#endif