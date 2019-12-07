#include "Token.hpp"

using namespace scanner;

Token::Token() : type(Type::Eof) {}

Token::Token(int value) : type(Type::Integer) {
    val = value;
}

Token::Token(std::string string) : type(Type::String) {
    val = string;
}

std::string Token::toString() const {
    return toString(type);
}

std::string Token::toString(Token::Type type) {
    switch (type)
    {
    case Type::Eof:
        return "EOF";
    case Type::Integer:
        return "int";
    case Type::String:
        return "string";
    }
    return "unknown";
}

std::string Token::valToString() const {
    switch (type)
    {
    case Type::Integer:
        return std::to_string(boost::get<int>(val));
    case Type::String:
        return boost::get<std::string>(val);
    }
    return std::string();
}