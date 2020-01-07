#ifndef SCANNER_TOKEN_HPP_
#define SCANNER_TOKEN_HPP_

#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include "TokenType.hpp"
#include "TokenTypeWrapper.hpp"

namespace scanner
{

class Token
{
public:
    Token();
    Token(int);
    Token(float);
    Token(std::string);
    Token(TokenType);
    Token(TokenType, std::string);

    TokenType getType() const { return type; }
    int getInteger() const { return std::get<int>(val); }
    float getFloat() const { return std::get<float>(val); }
    std::string getString() const { return std::get<std::string>(val); }
    std::string toString() const;

    static std::string toString(TokenType);
    std::string valToString() const;

private:
    TokenType type;
    static TokenTypeWrapper TTW;

    bool isFloat;

    std::variant<
        int,
        float,
        std::string
    > val;
};

inline std::ostream& operator<<(std::ostream& o, TokenType type) {
    return o << Token::toString(type);
}

}

#endif