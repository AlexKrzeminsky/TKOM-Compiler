#ifndef AST_PROGRAM_HPP_
#define AST_PROGRAM_HPP_

#include <unordered_map>
#include <memory>
#include "statement/FunctionDefStatement.hpp"

namespace ast
{

class Program
{
public:
    Program() {}

    void addFunction(std::unique_ptr<FunctionDefinition> newFunc) {
        functions.insert({newFunc->getId(), std::move(newFunc)});
    }

    FunctionDefinition &findFunction(std::string identifier) {
        return *functions.at(identifier);
    }

    bool existFunction(const std::string &identifier) {
        return functions.count(identifier);
    }

    FunctionDefinition &getMain() {
        return *functions.at("main");
    }

private:
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions;
};

}

#endif