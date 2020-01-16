#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <stdexcept>
#include <boost/variant.hpp>
#include <boost/log/trivial.hpp>
#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenCheck.hpp"
#include "TokenTypeWrapper.hpp"
#include "../reader/Reader.hpp"

namespace scanner
{
class Scanner {
public:
    Scanner(std::istream &istream);
    ~Scanner() { delete text; }
    bool scanNumber();
    bool scanString();
    bool scanIdentifier();
    void skipWhitespaces();
    void moveWhitespace();
    void nextLine();
    Token checkTwoCharToken(const char&, TokenType, TokenType);
    Token scan();
    const Token getToken() const { return token; }

    std::vector<Token> getTokens() {
        if (!scanFail) return tokens;
        else return std::vector<Token>();
    }
    
    TokenType getKeywordOrIdentifier();
    std::string tokenValue;

    bool fail;

    bool scanFail;
    int pos;
    int line;

    int callPos;
    int callLine;
private: 
    inline void move() {
        pos++;
        ch = text->peek();
        tokenValue += text->get();
    }

    Reader* text;

    char ch;

    Token token;
    std::vector<Token> tokens;
};
}

#endif