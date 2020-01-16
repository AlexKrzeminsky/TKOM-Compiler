#ifndef PARSER_LENSTATEMENT_HPP_
#define PARSER_LENSTATEMENT_HPP_

#include <list>
#include <memory>
#include "Statement.hpp"
#include "../expression/Expression.hpp"
#include "FunctionDefStatement.hpp"

namespace ast {

class LenStatement : public Statement {
public:
    explicit LenStatement(Var& var_) : var(var_) {}

    Return run() override {
        int size = var.value.size();
        Var var(VarType::INT, valueVec({size}));
        return Return(Return::None, var);
    }

private:
    Var& var;
};

}


#endif