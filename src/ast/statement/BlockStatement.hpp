#ifndef AST_BLOCKSTATEMENT_HPP_
#define AST_BLOCKSTATEMENT_HPP_

#include "Statement.hpp"
#include "../Var.hpp"
#include <map>
#include <vector>
#include <stdexcept>

namespace ast
{
using stmtPtr = std::unique_ptr<Statement>;

class BlockStatement : public Statement
{
public:
    BlockStatement(BlockStatement *parent_ = nullptr) : parent(parent_) {}
    
    const BlockStatement* getParent() const { return parent; }

    void addStatement(stmtPtr stmt) { statements.push_back(std::move(stmt)); }

    void addVariable(const std::string& id, Var&& var) { variables.insert({id, var}); }

    bool existVariable(const std::string& id) { 
        return variables.count(id) || (parent ? parent->existVariable(id) : false);
    }

    Var& findVariable(const std::string& id) {
        if (variables.count(id)) return variables.at(id);
        else if (parent) return parent->findVariable(id);
        else throw std::runtime_error("var not found");
    }

private:
    BlockStatement* parent;
    std::vector<stmtPtr> statements;
    std::map<std::string, Var> variables;
};

}

#endif