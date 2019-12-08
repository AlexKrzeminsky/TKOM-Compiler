#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <boost/variant.hpp>
#include <boost/log/trivial.hpp>
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
    bool scanString();
    bool scanIdentifier();
    void nextLine();
    Token scan();
    TokenType getKeywordOrIdentifier();
    std::string tokenValue;

    bool fail;

private: 
    std::ifstream text;
    inline void move() {
        pos++;
        tokenValue += text.get();
    }
    static TokenTypeWrapper TTW;

    int callPos;
    int callLine;
    int pos;
    int line;

    bool isFloat();
    bool isClear();
};
}

#endif