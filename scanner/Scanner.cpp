#define BOOST_LOG_DYN_LINK 1
#include "Scanner.hpp"

using namespace scanner;

Scanner::Scanner(std::string path) {
    fail = false;
    text = std::ifstream(path);

    if ( text.fail() ) {
        fail = true;
    } 

    pos = 0;
    line = 1;

    TokenTypeWrapper::getInstance();
}

bool Scanner::isFloat() {
    return (tokenValue.find('.') != std::string::npos);
}

bool Scanner::isClear() {
    char tmp = text.peek();
    return (isWhitespace(tmp) ||
            (tmp >= '!' && tmp <= '/') ||
            (tmp >= ':' && tmp <= '>') ||
            tmp == '{' ||
            tmp == '}' ||
            tmp == '[' ||
            tmp == ']'
            );
}

bool Scanner::scanNumber() {
    bool clearNumber = true;
    while (isDigit(text.peek())) move();
    if (text.peek() == '.') {
        move();
        while (isDigit(text.peek())) move();
    }
    if (!isClear()) {
        while (!isClear()) move();
        BOOST_LOG_TRIVIAL(error) << std::to_string(line) + ":" + std::to_string(callPos)
            + " - Incorrectly defined literal'" + tokenValue + "'\n";
        clearNumber = false;
    }
    return clearNumber;
}

bool Scanner::scanString() {
    bool closed = false;
    while (true) {
        if (text.eof()) break;
        if (text.peek() == '"'){
            move();
            closed = true;
            break;
        }
        if (isLineBreak(text.peek())) {
            nextLine();
            break;
        }
        move();
    }
    if (!closed) {
        BOOST_LOG_TRIVIAL(error) << std::to_string(line) + ":" + std::to_string(callPos)
            + " - Incorrectly defined string: '" + tokenValue + "'\n";
        tokenValue = std::string(); 
    }
    return closed;
}

bool Scanner::scanIdentifier() {
    bool clearIdentifier = true;
    while (isIdentifierPart(text.peek())) move();
    if (!isClear()) {
        while (!isClear()) move();
        BOOST_LOG_TRIVIAL(error) << std::to_string(line) + ":" + std::to_string(callPos)
            + " - Incorrectly defined identifier'" + tokenValue + "'\n";
        clearIdentifier = false;
    }
    return clearIdentifier;
}

void Scanner::nextLine() {
    line += 1;
    pos = 0;

}

TokenType Scanner::getKeywordOrIdentifier() {
    TokenType token;
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
        callPos = pos;
        callLine = line;

        if (text.eof()) return Token(TokenType::T_EOF);

        if (isLineBreak(ch)) {
            tokenValue = std::string();
            nextLine();
            continue;
        }

        if (isWhitespace(ch)) {
            tokenValue = std::string();
            continue;
        }

        switch (ch) {
            case '"':
                if (!scanString()) return Token(TokenType::UNDEFINED);
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
                if(!scanNumber()) return Token(TokenType::UNDEFINED);

                if(isFloat()) return Token(std::stof(tokenValue));
                else return Token(std::stoi(tokenValue));
            default:
                if (isIdentifierStart(ch)) {
                    if (!scanIdentifier()) return Token(TokenType::UNDEFINED);
                    return Token(getKeywordOrIdentifier());                    
                }
                BOOST_LOG_TRIVIAL(error) << std::to_string(line) + ":" + std::to_string(pos)
                    + " - Unknown Token: '" + tokenValue + "'\n";
                return Token(TokenType::UNDEFINED);
        }
    }
}
