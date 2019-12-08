#include "Token.hpp"

using namespace scanner;

Token::Token() : type(TokenType::T_EOF) { TokenTypeWrapper::getInstance(); }

Token::Token(int value) : type(TokenType::L_Numeric) {
    val = value;
    TokenTypeWrapper::getInstance();
}

Token::Token(std::string string) : type(TokenType::L_String) {
    val = string;
    TokenTypeWrapper::getInstance();
}

Token::Token(TokenType ttype) : type(ttype) { TokenTypeWrapper::getInstance(); }

std::string Token::toString() const {
    return toString(type);
}

std::string Token::toString(TokenType type) {
    return TTW.typeToString(type);
}

std::string Token::valToString() const {
    switch (type)
    {
    case TokenType::L_Numeric:
        return std::to_string(boost::get<int>(val));
    case TokenType::L_String:
        return boost::get<std::string>(val);
    default:
        return std::string();
    }
    return std::string();
}