#include "Token.hpp"

using namespace scanner;

Token::Token() : type(TokenType::Type::T_EOF) {}

Token::Token(int value) : type(TokenType::Type::L_Numeric) {
    val = value;
}

Token::Token(std::string string) : type(TokenType::Type::L_String) {
    val = string;
}

std::string Token::toString() const {
    return toString(type);
}

std::string Token::toString(TokenType::Type type) {
    switch (type)
    {
    case TokenType::Type::T_EOF:
        return "EOF";
    case TokenType::Type::L_Numeric:
        return "int";
    case TokenType::Type::L_String:
        return "string";
    }
    return "unknown";
}

std::string Token::valToString() const {
    switch (type)
    {
    case TokenType::Type::L_Numeric:
        return std::to_string(boost::get<int>(val));
    case TokenType::Type::L_String:
        return boost::get<std::string>(val);
    }
    return std::string();
}