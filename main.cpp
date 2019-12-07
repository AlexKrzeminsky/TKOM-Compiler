#include "scanner/Token.hpp"
#include "scanner/TokenType.hpp"
#include "scanner/TokenTypeWrapper.hpp"
#include <iostream>
#include <string>

using namespace scanner;

int main() {
    typedef TokenTypeWrapper TTW;
    Token token1;
    Token token2(12);
    Token token3("abc");
    TTW::getInstance();

    std::cout << token1.toString() << token1.valToString() << std::endl;
    std::cout << token2.toString() << token2.valToString() << std::endl;
    std::cout << token3.toString() << token3.valToString() << std::endl;

    //std::cout << TokenTypeWrapper::typeToString(token1.getType());
    std::string test = TTW::typeToString(TTW::stringToType(">="));

    std::cout << test;

    return 0;
}