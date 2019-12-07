#include "TokenType.hpp"

using namespace scanner;


std::map<TokenType::Type, std::string> TokenType::reverseMap
(std::map<std::string, TokenType::Type> stmap){
    std::map<TokenType::Type, std::string> result;

    for (auto &i: stmap) {
        result[i.second] = i.first;
    }

    return result;
}

std::string TokenType::typeToString(TokenType::Type type){
    std::map<TokenType::Type, std::string>::iterator it;

    it = tokenStringMap.find(type);
    return it->second; 
}

TokenType::Type TokenType::stringToType(std::string str){
    std::map<std::string, TokenType::Type>::iterator it;

    it = stringTokenMap.find(str);
    return it->second; 
}