#include "TokenTypeWrapper.hpp"

using namespace scanner;

TokenTypeWrapper& TokenTypeWrapper::getInstance(){
    static TokenTypeWrapper instance;
    return instance;
}

TokenTypeWrapper::STMap_ TokenTypeWrapper::stringTokenMap = {
    {"fun",         TokenType::K_Fun},          
    {"return",      TokenType::K_Return},       
    {"break",       TokenType::K_Break},        
    {"continue",    TokenType::K_Continue},     
    {"if",          TokenType::K_If},           
    {"else",        TokenType::K_Else},         
    {"while",       TokenType::K_While},        
    {"var",         TokenType::K_Var},          
    {"{",           TokenType::T_OpenBrace},    
    {"}",           TokenType::T_CloseBrace},   
    {"(",           TokenType::T_OpenParen},    
    {")",           TokenType::T_CloseParen},   
    {"[",           TokenType::T_OpenBracket},  
    {"]",           TokenType::T_CloseBracket}, 
    {";",           TokenType::T_Semicolon},    
    {".",           TokenType::T_Dot},          
    {",",           TokenType::T_Comma},        
    {"=",           TokenType::T_Equal},        
    {"==",          TokenType::T_Equal2},       
    {"!=",          TokenType::T_NotEqual},     
    {"<",           TokenType::T_LessThan},     
    {">",           TokenType::T_GreaterThan},  
    {"<=",          TokenType::T_LeEqThan},     
    {">=",          TokenType::T_GrEqThan},     
    {"+",           TokenType::T_Plus},         
    {"-",           TokenType::T_Minus},        
    {"*",           TokenType::T_Asterisk},     
    {"/",           TokenType::T_Slash},        
    {"||",          TokenType::T_Bar2},         
    {"&&",          TokenType::T_Ampersand2},
};

TokenTypeWrapper::TSMap_ TokenTypeWrapper::tokenStringMap = 
    TokenTypeWrapper::reverseMap(stringTokenMap);

std::string TokenTypeWrapper::typeToString(TokenType type){
    TSMap_::iterator it;

    it = tokenStringMap.find(type);
    return it->second; 
}

TokenType TokenTypeWrapper::stringToType(std::string str){
    STMap_::iterator it;

    it = stringTokenMap.find(str);
    return it->second; 
}