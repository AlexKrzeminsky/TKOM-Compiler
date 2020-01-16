#ifndef PARSER_RETURN_HPP
#define PARSER_RETURN_HPP

#include <utility>
#include "Var.hpp"

namespace ast {

struct Return {
    enum Type {
        None,
        Variable,
        Break,
        Continue
    };

    explicit Return(Type type = Type::None) : type(type) {}

    explicit Return(Type type, Var variable) : type(type), variable(std::move(variable)) {}

    Type type;
    Var variable;
};

}


#endif //INTERPRETER_RETURN_HPP