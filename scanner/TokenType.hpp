#ifndef SCANNER_TOKENTYPE_H_
#define SCANNER_TOKENTYPE_H_

#include <map>
#include <string>

namespace scanner
{

class TokenType
{
public:
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
    // map without Identifiers and Literals
    std::map<std::string, Type> stringTokenMap = {
        {"fun",         Type::K_Fun},          
        {"return",      Type::K_Return},       
        {"break",       Type::K_Break},        
        {"continue",    Type::K_Continue},     
        {"if",          Type::K_If},           
        {"else",        Type::K_Else},         
        {"while",       Type::K_While},        
        {"var",         Type::K_Var},          
        {"{",           Type::T_OpenBrace},    
        {"}",           Type::T_CloseBrace},   
        {"(",           Type::T_OpenParen},    
        {")",           Type::T_CloseParen},   
        {"[",           Type::T_OpenBracket},  
        {"]",           Type::T_CloseBracket}, 
        {";",           Type::T_Semicolon},    
        {".",           Type::T_Dot},          
        {",",           Type::T_Comma},        
        {"=",           Type::T_Equal},        
        {"==",          Type::T_Equal2},       
        {"!=",          Type::T_NotEqual},     
        {"<",           Type::T_LessThan},     
        {">",           Type::T_GreaterThan},  
        {"<=",          Type::T_LeEqThan},     
        {">=",          Type::T_GrEqThan},     
        {"+",           Type::T_Plus},         
        {"-",           Type::T_Minus},        
        {"*",           Type::T_Asterisk},     
        {"/",           Type::T_Slash},        
        {"||",          Type::T_Bar2},         
        {"&&",          Type::T_Ampersand2},
    };

    std::map<Type, std::string> reverseMap(std::map<std::string, Type>);
    std::map<Type, std::string> tokenStringMap = reverseMap(stringTokenMap);
};

}

#endif