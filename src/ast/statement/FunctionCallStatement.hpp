#ifndef PARSER_FUNCALLSTATEMENT_HPP_
#define PARSER_FUNCALLSTATEMENT_HPP_

#include <list>
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

    Return run() override {
        std::list<Var> var;
        for (auto &&expr : expressions) {
            var.push_back(expr->calculate());
        }
        Return ret = functionDef.run(var);
        ret.type = Return::None;
        return ret;
    }

private:
    FunctionDefinition &functionDef;
    std::list<std::unique_ptr<Expression>> expressions;
};

}


#endif