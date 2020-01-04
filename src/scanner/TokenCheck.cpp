#include "TokenCheck.hpp"

bool isDigit(const char& ch) {
    return (ch >= '0' && ch <= '9');
}

bool isLineBreak(const char& ch) {
    return (ch == '\n' ||
            ch == '\r');
}

bool isWhitespace(const char& ch) {
    return (ch == ' ' || 
            ch == '\t' || 
            ch == '\v');
}

bool isIdentifierStart(const char& ch) {
    return (ch >= 'a' && ch <= 'z') || 
           (ch >= 'A' && ch <= 'Z');
}

bool isIdentifierPart(const char& ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           ch == '_';
}

bool isClearNumber(const char& ch) {
    return (isWhitespace(ch) ||
            ch == '+'  ||
            ch == '-'  ||
            ch == '/'  ||
            ch == '*'  ||
            ch == ';'  ||
            ch == '('  ||
            ch == ')'  ||
            ch == '&'  ||
            ch == '|'  ||
            ch == '!'  ||
            ch == ']'  ||
            ch == '='  ||
            (ch >= '<' && ch <= '>'));
}

bool isClearIdentifier(const char& ch) {
    return (isClearNumber(ch) ||
            ch == '[');
}

bool isFloat(const std::string& tokenV) {
    return (tokenV.find('.') != std::string::npos);
}