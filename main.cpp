#include "scanner/Token.hpp"
#include "scanner/TokenType.hpp"
#include "scanner/TokenTypeWrapper.hpp"
#include "scanner/Scanner.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace scanner;

int main() {
    typedef TokenTypeWrapper TTW;
    TTW::getInstance();
    std::vector<Token> tokens;
    Token token;
    Scanner scanner("test.txt");
    while(true) {
        token = scanner.scan();
        tokens.push_back(token);
        if (token.getType() == TokenType::T_EOF) break;
    }

    for (auto &i: tokens) {
        std::cout << i.toString() << std::endl;
    }

    return 0;
}