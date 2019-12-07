#ifndef SCANNER_TOKEN_HPP_
#define SCANNER_TOKEN_HPP_

#include <string>
#include <boost/variant.hpp>

namespace scanner
{

class Token
{
public:
    enum class Type
    {
        Eof,
        Integer,
        String,
    };


    Token();
    Token(int value);
    Token(std::string str);

    Type getType() const { return type; }
    int getInteger() const { return boost::get<int>(val); }
    std::string getString() const { return boost::get<std::string>(val); }
    std::string toString() const;

    static std::string toString(Token::Type type);
    std::string valToString() const;

private:
    Type type;

    boost::variant<
        int,
        std::string
    > val;
};

inline std::ostream& operator<<(std::ostream& o, Token::Type type) {
    return o << Token::toString(type);
}

};

#endif