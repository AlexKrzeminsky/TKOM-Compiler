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

    TokenType::Type getType() const { return type; }
    int getInteger() const { return boost::get<int>(val); }
    std::string getString() const { return boost::get<std::string>(val); }
    std::string toString() const;

    static std::string toString(TokenType::Type);
    std::string valToString() const;

private:
    TokenType::Type type;

    boost::variant<
        int,
        std::string
    > val;
};

inline std::ostream& operator<<(std::ostream& o, TokenType::Type type) {
    return o << Token::toString(type);
}

};

#endif