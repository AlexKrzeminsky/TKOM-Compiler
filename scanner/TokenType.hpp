#ifndef SCANNER_TOKENTYPE_H_
#define SCANNER_TOKENTYPE_H_

#include <map>
#include <string>

namespace scanner
{

class TokenType
{
    // K_ - Keyword
    // T_ - Token
    // I_ - Identifier
    // L_ - Literals
    enum class Type {
        K_Fun,          // fun
        K_Return,       // return
        K_Break,        // break
        K_Continue,     // continue
        K_If,           // if
        K_Else,         // else
        K_While,        // while
        K_Var,          // var
        T_OpenBrace,    // {
        T_CloseBrace,   // }
        T_OpenParen,    // (
        T_CloseParen,   // )
        T_OpenBracket,  // [
        T_CloseBracket, // ]
        T_Semicolon,    // ;
        T_Dot,          // .
        T_Comma,        // ,
        T_Equal,        // =
        T_Equal2,       // ==
        T_NotEqual,     // !=
        T_LessThan,     // <
        T_GreaterThan,  // >
        T_LeEqThan,     // <=
        T_GrEqThan,     // >=
        T_Plus,         // +
        T_Minus,        // -
        T_Asterisk,     // *
        T_Slash,        // /
        T_Bar2,         // ||
        T_Ampersand2,   // &&
        T_EOF,          // EOF
        I_Identifier,   // identifier
        L_String,       // string literal
        L_Numeric,      // numeric literal
    };

    TokenType(TokenType::Type type) : type(type) {}

    Type type;

    std::string typeToString(Type);
    Type stringToType(std::string);

private:
    std::map<std::string, Type> stringTokenMap = {
        {"fun",         K_Fun},          
        {"return",      K_Return},       
        {"break",       K_Break},        
        {"continue",    K_Continue},     
        {"if",          K_If},           
        {"else",        K_Else},         
        {"while",       K_While},        
        {"var",         K_Var},          
        {"{",           T_OpenBrace},    
        {"}",           T_CloseBrace},   
        {"(",           T_OpenParen},    
        {")",           T_CloseParen},   
        {"[",           T_OpenBracket},  
        {"]",           T_CloseBracket}, 
        {";",           T_Semicolon},    
        {".",           T_Dot},          
        {",",           T_Comma},        
        {"=",           T_Equal},        
        {"==",          T_Equal2},       
        {"!=",          T_NotEqual},     
        {"<",           T_LessThan},     
        {">",           T_GreaterThan},  
        {"<=",          T_LeEqThan},     
        {">=",          T_GrEqThan},     
        {"+",           T_Plus},         
        {"-",           T_Minus},        
        {"*",           T_Asterisk},     
        {"/",           T_Slash},        
        {"||",          T_Bar2},         
        {"&&",          T_Ampersand2},
    };

    std::map<Type, std::string> reverseMap(std::map<std::string, Type>);
    std::map<Type, std::string> tokenStringMap = reverseMap(stringTokenMap);
};

}

#endif