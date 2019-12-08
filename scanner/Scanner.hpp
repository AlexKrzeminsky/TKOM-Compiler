#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <boost/variant.hpp>
#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenCheck.hpp"
#include "TokenTypeWrapper.hpp"

namespace scanner
{
class Scanner {
public:
    Scanner(std::string);
    bool scanNumber();
    void scanString();
    void scanIdentifier();
    Token scan();
    TokenType getKeywordOrIdentifier();
    std::string tokenValue;

private: 
    std::ifstream text;
    inline void move() {
        tokenValue += text.get();
    }
    static TokenTypeWrapper TTW;

    int start;
    int pos;
    int end;

    TokenType token;
    int tokenPos;
};
}

#endif