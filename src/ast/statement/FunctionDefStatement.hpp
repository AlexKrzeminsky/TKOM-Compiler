#ifndef AST_FUNCTIONDEFSTATEMENT_HPP_
#define AST_FUNCTIONDEFSTATEMENT_HPP_

#include <string>
#include <list>
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

    Return run(std::list<Var> var = std::list<Var>()) {
        auto itParameters = vars.begin();
        auto itVar = var.begin();

        for (; itVar != var.end(); ++itVar, ++itParameters) {
            block.findVariable(*itParameters) = *itVar;
        }

        Return ret = block.run();

        return ret;
    };

private:
    std::string id;
    std::list<std::string> vars;
    BlockStatement block;
};

}

#endif