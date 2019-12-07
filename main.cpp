#include "scanner/Token.hpp"
#include <iostream>
#include <string>


int main() {
    scanner::Token* token1 = new scanner::Token();
    scanner::Token* token2 = new scanner::Token(12);
    scanner::Token* token3 = new scanner::Token("abc");

    std::cout << token1->toString() << token1->valToString() << std::endl;
    std::cout << token2->toString() << token2->valToString() << std::endl;
    std::cout << token3->toString() << token3->valToString() << std::endl;

    delete token1;
    delete token2;
    delete token3;
}