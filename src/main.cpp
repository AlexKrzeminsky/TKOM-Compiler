#define BOOST_LOG_DYN_LINK 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include "scanner/Token.hpp"
#include "scanner/TokenType.hpp"
#include "scanner/TokenTypeWrapper.hpp"
#include "scanner/Scanner.hpp"
#include "parser/Parser.hpp"

using namespace scanner;
using namespace parser;

typedef std::vector<Token> t_vec;

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
    
    std::ifstream f;
    f.open(argv[1]);
    if(!f.good()) {
        BOOST_LOG_TRIVIAL(error) << "Error occured when tried to open given path";
        return -2;
    }
    Scanner scr(f);
    Parser parser(&scr);
    try {
        parser.parse();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    f.close();

    return 0;
}