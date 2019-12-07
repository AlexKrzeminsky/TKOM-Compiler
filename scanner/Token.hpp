#ifndef SCANNER_TOKEN_HPP_
#define SCANNER_TOKEN_HPP_

#include <string>
#include <boost/variant.hpp>
#include "TokenType.hpp"

namespace scanner
{

class Token
{
public:
    Token();
    Token(int);
    Token(std::string);

    TokenType getType() const { return type; }
    int getInteger() const { return boost::get<int>(val); }
    std::string getString() const { return boost::get<std::string>(val); }
    std::string toString() const;

    static std::string toString(TokenType);
    std::string valToString() const;

private:
    TokenType type;

    boost::variant<
        int,
        std::string
    > val;
};

inline std::ostream& operator<<(std::ostream& o, TokenType type) {
    return o << Token::toString(type);
}

};

#endif