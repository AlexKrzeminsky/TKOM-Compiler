#include "TokenTypeWrapper.hpp"
#include <iostream>
using namespace scanner;

TokenTypeWrapper& TokenTypeWrapper::getInstance(){
    static TokenTypeWrapper instance;
    return instance;
}

TokenTypeWrapper::STMap_ TokenTypeWrapper::reprTokenMap = {
    {"fun",         TokenType::K_Fun},          
    {"return",      TokenType::K_Return},       
    {"break",       TokenType::K_Break},        
    {"continue",    TokenType::K_Continue},     
    {"if",          TokenType::K_If},           
    {"else",        TokenType::K_Else},         
    {"while",       TokenType::K_While},        
    {"var",         TokenType::K_Var},  
    {"append",      TokenType::K_Append},     
    {"len",         TokenType::K_Len},   
    {"{",           TokenType::T_OpenBrace},    
    {"}",           TokenType::T_CloseBrace},   
    {"(",           TokenType::T_OpenParen},    
    {")",           TokenType::T_CloseParen},   
    {"[",           TokenType::T_OpenBracket},  
    {"]",           TokenType::T_CloseBracket}, 
    {":",           TokenType::T_Colon},
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
    {"!",           TokenType::T_Exclamation},    
    {"+",           TokenType::T_Plus},         
    {"-",           TokenType::T_Minus},        
    {"*",           TokenType::T_Asterisk},     
    {"/",           TokenType::T_Slash},        
    {"||",          TokenType::T_Bar2},         
    {"&&",          TokenType::T_Ampersand2},
};

TokenTypeWrapper::TSMap_ TokenTypeWrapper::tokenStringMap = {
    {TokenType::UNDEFINED,      "UNDEFINED"},
    {TokenType::K_Fun,          "K_Fun"},
    {TokenType::K_Return,       "K_Return"}, 
    {TokenType::K_Break,        "K_Break"},
    {TokenType::K_Continue,     "K_Continue"},
    {TokenType::K_If,           "K_If"},
    {TokenType::K_Else,         "K_Else"},
    {TokenType::K_While,        "K_While"},
    {TokenType::K_Var,          "K_Var"},
    {TokenType::K_Append,       "K_Append"},
    {TokenType::K_Len,          "K_Len"},
    {TokenType::T_OpenBrace,    "T_OpenBrace"},
    {TokenType::T_CloseBrace,   "T_CloseBrace"},
    {TokenType::T_OpenParen,    "T_OpenParen"},
    {TokenType::T_CloseParen,   "T_CloseParen"},
    {TokenType::T_OpenBracket,  "T_OpenBracket"},
    {TokenType::T_CloseBracket, "T_CloseBracket"},
    {TokenType::T_Colon,        "T_Colon"},
    {TokenType::T_Semicolon,    "T_Semicolon"},
    {TokenType::T_Dot,          "T_Dot"},
    {TokenType::T_Comma,        "T_Comma"},
    {TokenType::T_Equal,        "T_Equal"},  
    {TokenType::T_Equal2,       "T_Equal2"},
    {TokenType::T_NotEqual,     "T_NotEqual"},
    {TokenType::T_LessThan,     "T_LessThan"},
    {TokenType::T_GreaterThan,  "T_GreaterThan"},
    {TokenType::T_LeEqThan,     "T_LeEqThan"},
    {TokenType::T_GrEqThan,     "T_GrEqThan"},
    {TokenType::T_Exclamation,  "T_Exclamation"},
    {TokenType::T_Plus,         "T_Plus"},
    {TokenType::T_Minus,        "T_Minus"},   
    {TokenType::T_Asterisk,     "T_Asterisk"},
    {TokenType::T_Slash,        "T_Slash"},
    {TokenType::T_Bar2,         "T_Bar2"},
    {TokenType::T_Ampersand2,   "T_Ampersand2"},
    {TokenType::T_EOF,          "T_EOF"},
    {TokenType::I_Identifier,   "I_Identifier"},
    {TokenType::L_String,       "L_String"},
    {TokenType::L_Numeric,      "L_Numeric"},
};

TokenTypeWrapper::TSMap_ TokenTypeWrapper::tokenReprMap = 
    TokenTypeWrapper::reverseMap(reprTokenMap);

std::string TokenTypeWrapper::typeToRepr(TokenType type){
    TSMap_::iterator it;

    it = tokenReprMap.find(type);
    if (std::end(tokenReprMap) == it) return "UNDEFINED";
    return it->second; 
}

std::string TokenTypeWrapper::typeToString(TokenType type){
    TSMap_::iterator it;

    it = tokenStringMap.find(type);
    if (std::end(tokenStringMap) == it) return "UNDEFINED";
    return it->second; 
}

TokenType TokenTypeWrapper::reprToType(std::string str){
    STMap_::iterator it;

    it = reprTokenMap.find(str);
    if (std::end(reprTokenMap) == it) return TokenType::UNDEFINED;
    return it->second; 
}