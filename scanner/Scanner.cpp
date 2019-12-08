#include "Scanner.hpp"

using namespace scanner;

Scanner::Scanner(std::string path) {
    text = std::ifstream(path);

    TokenTypeWrapper::getInstance();
}

bool Scanner::scanNumber() {
    bool is_float = false;
    while (isDigit(text.peek())) move();
    if (text.peek() == '.') {
        move();
        while (isDigit(text.peek())) move();
        is_float = true;
    }
    return is_float;
}

void Scanner::scanString() {
    bool closed = false;
    while (true) {
        if (text.peek() == '"'){
            move();
            closed = true;
            break;
        }
        move();
    }
    if (!closed) {
        tokenValue = std::string(); 
        token = TokenType::UNDEFINED;
    }
}

void Scanner::scanIdentifier() {
    while (isIdentifierPart(text.peek())) move();
}

TokenType Scanner::getKeywordOrIdentifier() {
    if (tokenValue[0] >= 'a' && tokenValue[0] <= 'z') {
        token = TTW.reprToType(tokenValue);
    }
    if(token == TokenType::UNDEFINED)
        token = TokenType::I_Identifier;

    return token;
}

Token Scanner::scan() {
    tokenValue = std::string();
    while (true) {
        char ch = text.peek();
        move();
        char tmp;
        bool is_float;

        if (text.eof()) return Token(TokenType::T_EOF);

        if (isWhitespace(ch) || isLineBreak(ch)) {
            tokenValue = std::string(); 
            continue;
        }

        switch (ch) {
            case '"':
                scanString();
                if (token == TokenType::UNDEFINED) return Token(TokenType::UNDEFINED);
                return Token(tokenValue);
            case '&':
                if (text.peek() == '&') {
                    move();
                    return Token(TokenType::T_Ampersand2);
                }
            case '|':
                if (text.peek() == '|') {
                    move();
                    return Token(TokenType::T_Bar2);
                }
            case '(':
            case ')':
            case '[':
            case ']':
            case '{':
            case '}':
            case ';':
            case ':':
            case '.':
            case ',':
            case '+':
            case '-':
            case '*':
            case '/':
                return Token(TTW.reprToType(tokenValue));
            case '=':
                if (text.peek() == '=') {
                    move();
                    return Token(TokenType::T_Equal2);
                }
                return Token(TokenType::T_Equal);
            case '>':
                if (text.peek() == '=') {
                    move();
                    return Token(TokenType::T_GrEqThan);
                }
                return Token(TokenType::T_GreaterThan);
            case '<':
                if (text.peek() == '=') {
                    move();
                    return Token(TokenType::T_GrEqThan);
                }
                return Token(TokenType::T_GreaterThan);
            case '!':
                if (text.peek() == '=') {
                    move();
                    return Token(TokenType::T_GrEqThan);
                }
                return Token(TokenType::T_Exclamation);
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tmp = text.peek();
                is_float = scanNumber();
                if(is_float) return Token(std::stof(tokenValue));
                else return Token(std::stoi(tokenValue));
            default:
                if (isIdentifierStart(ch)) {
                    tmp = text.peek();
                    while(isIdentifierPart(tmp)) {
                        move(); 
                        tmp = text.peek();
                    }
                    return Token(getKeywordOrIdentifier());                    
                }
                return Token(TokenType::UNDEFINED);
        }
    }
}
