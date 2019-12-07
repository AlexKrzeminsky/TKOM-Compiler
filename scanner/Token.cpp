#include "Token.hpp"

using namespace scanner;

Token::Token() : type(TokenType::T_EOF) {}

Token::Token(int value) : type(TokenType::L_Numeric) {
    val = value;
}

Token::Token(std::string string) : type(TokenType::L_String) {
    val = string;
}

std::string Token::toString() const {
    return toString(type);
}

std::string Token::toString(TokenType type) {
    switch (type)
    {
    case TokenType::T_EOF:
        return "EOF";
    case TokenType::L_Numeric:
        return "int";
    case TokenType::L_String:
        return "string";
    }
    return "unknown";
}

std::string Token::valToString() const {
    switch (type)
    {
    case TokenType::L_Numeric:
        return std::to_string(boost::get<int>(val));
    case TokenType::L_String:
        return boost::get<std::string>(val);
    }
    return std::string();
}