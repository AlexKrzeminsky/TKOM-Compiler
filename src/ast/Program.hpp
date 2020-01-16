#ifndef AST_PROGRAM_HPP_
#define AST_PROGRAM_HPP_

#include <unordered_map>
#include <memory>
#include "statement/FunctionDefStatement.hpp"
#include "Return.hpp"

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

    Return run() {
        for (auto &&function : functions) {
            if (function.second->getId() == "main") {
                return function.second->run();
            }
        }
        throw std::runtime_error("Program doesn't contain main function");
    };

private:
    std::unordered_map<std::string, std::unique_ptr<FunctionDefinition>> functions;
};

}

#endif