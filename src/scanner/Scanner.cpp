#define BOOST_LOG_DYN_LINK 1
#include "Scanner.hpp"

using namespace scanner;

Scanner::Scanner(std::istream &istream)
        {
    text = new Reader(istream);
    pos = 0;
    line = 1;

    //TokenTypeWrapper::getInstance();
}

bool Scanner::scanNumber() {
    bool clearNumber = true;
    while (isDigit(text->peek())) move();
    if (text->peek() == '.') {
        move();
        while (isDigit(text->peek())) move();
    }
    if (!isClearNumber(text->peek())) {
        while (!isLineBreak(text->peek()) && !text->eof()) move();
        clearNumber = false;
    }
    return clearNumber;
}

bool Scanner::scanString() {
    bool closed = false;
    while (true) {
        if (text->eof()) break;
        if (text->peek() == '"'){
            move();
            closed = true;
            break;
        }
        if (isLineBreak(text->peek())) {
            nextLine();
            break;
        }
        move();
    }
    return closed;
}

bool Scanner::scanIdentifier() {
    bool clearIdentifier = true;
    while (isIdentifierPart(text->peek())) move();
    if (!isClearIdentifier(text->peek())) {
        while (!isLineBreak(text->peek()) && !text->eof()) move();
        clearIdentifier = false;
    }
    return clearIdentifier;
}

void Scanner::skipWhitespaces() {
    bool isWhitespaceCond = true;

    while (isWhitespaceCond) {
        if (isLineBreak(ch)) {
            moveWhitespace();
            nextLine();
            continue;
        }
        if (isWhitespace(ch)) {
            moveWhitespace();
            continue;
        }
        isWhitespaceCond = false;
    }
}


void Scanner::moveWhitespace() {
    tokenValue = std::string();
    move();
}

void Scanner::nextLine() {
    line += 1;
    pos = 0;
}

TokenType Scanner::getKeywordOrIdentifier() {
    TokenType tokenType = TokenType::UNDEFINED;
    if (tokenValue[0] >= 'a' && tokenValue[0] <= 'z') {
        tokenType = TokenTypeWrapper::reprToType(tokenValue);
    }
    if(tokenType == TokenType::UNDEFINED)
        tokenType = TokenType::I_Identifier;

    return tokenType;
}

Token Scanner::checkTwoCharToken(const char& expected, TokenType twoCharType, TokenType oneCharType) {
    if (text->peek() == expected) {
        move();
        return Token(twoCharType);
    }
    return Token(oneCharType);
}

Token Scanner::scan() {
    Token tk;
    tokenValue = std::string();
    move();

    callPos = pos;
    callLine = line;

    skipWhitespaces();

    if (text->eof()) {
        token = Token(TokenType::T_EOF);
        return token;
    }

    switch (ch) {
        case '"':
            if (!scanString()) { 
                tk = Token(TokenType::UNDEFINED);
                break;
            }
            tk = Token(tokenValue);
            break;
        case '&':
            tk = checkTwoCharToken('&', TokenType::T_Ampersand2, TokenType::UNDEFINED);
            break;
        case '|':
            tk = checkTwoCharToken('|', TokenType::T_Bar2, TokenType::UNDEFINED);
            break;
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
            tk = Token(TokenTypeWrapper::reprToType(tokenValue));
            break;
        case '=':
            tk = checkTwoCharToken('=', TokenType::T_Equal2, TokenType::T_Equal);
            break;
        case '>':
            tk = checkTwoCharToken('=', TokenType::T_GrEqThan, TokenType::T_GreaterThan);
            break;
        case '<':
            tk = checkTwoCharToken('=', TokenType::T_LeEqThan, TokenType::T_LessThan);
            break;
        case '!':
            tk = checkTwoCharToken('=', TokenType::T_NotEqual, TokenType::T_Exclamation);
            break;
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
            if(!scanNumber()) tk = Token(TokenType::UNDEFINED);
            else {
                if(isFloat(tokenValue)) tk = Token(std::stof(tokenValue));
                else tk = Token(std::stoi(tokenValue));
            }
            break;

        default:
            if (isIdentifierStart(ch)) {
                if (!scanIdentifier()) { 
                    tk = Token(TokenType::UNDEFINED); 
                    break; 
                }
                tk = Token(getKeywordOrIdentifier(), tokenValue); 
                break;             
            }
            tk = Token(TokenType::UNDEFINED);
    }
    if (tk.getType() == TokenType::UNDEFINED) 
                    throw std::runtime_error(
                    std::to_string(line) + ":" + std::to_string(pos)
                    + " - Unknown Token: '" + tokenValue + "'\n");
    else { tokens.push_back(tk); token = tk; }
    std::cout << TokenTypeWrapper::typeToString(tk.getType()) << std::endl;
    return tk;
}