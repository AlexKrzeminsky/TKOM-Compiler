#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scanner/Token.hpp"
#include "scanner/TokenType.hpp"
#include "scanner/TokenTypeWrapper.hpp"
#include "scanner/Scanner.hpp"

using namespace scanner;

typedef std::vector<Token> t_vec;

t_vec scanForTokens(Scanner& scr) {
    Token token;
    t_vec tokens;

    while(true) {
        token = scr.scan();
        tokens.push_back(token);
        if (token.getType() == TokenType::T_EOF) break;
    }

    return tokens;
}

void printTokens(t_vec const& tokens) {
    for (auto &i: tokens) {
        std::cout << i.toString() + ": " + i.valToString() << std::endl;
    }
}

int main(int argc, char* argv[]) {

    if(argc != 2) {
        BOOST_LOG_TRIVIAL(error) << "Need to pass a path to code file!\n";
        return -1;
    }

    typedef TokenTypeWrapper TTW;
    TTW::getInstance();
    t_vec tokens;

    
    Scanner scr(argv[1]);
    if ( scr.fail ) {
        BOOST_LOG_TRIVIAL(error) << "Error occured when tried to open given path";
        return -2;
    }

    tokens = scanForTokens(scr);
    printTokens(tokens);

    return 0;
}