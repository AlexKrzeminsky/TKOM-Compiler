#ifndef AST_FUNCTIONDEFSTATEMENT_HPP_
#define AST_FUNCTIONDEFSTATEMENT_HPP_

#include <string>
#include <vector>
#include "../Var.hpp"
#include "../VarType.hpp"
#include "BlockStatement.hpp"

namespace ast
{

class FunctionDefinition
{
public:
    FunctionDefinition(std::string id_) : id(id_) {}

    void addParam(const std::string& id) {
        vars.push_back(id);
        block.addVariable(id, Var());
    }
    BlockStatement& getFunctionBlock() {
        return block;
    }
    const std::string& getId() const { return id; }

    unsigned size() { return vars.size(); }

private:
    std::string id;
    std::vector<std::string> vars;
    BlockStatement block;
};

}

#endif