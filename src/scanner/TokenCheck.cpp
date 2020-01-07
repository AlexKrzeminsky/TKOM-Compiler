#include "TokenCheck.hpp"
#include <cctype>

bool isDigit(const char& ch) {
    return std::isdigit(ch);
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
    return std::isalpha(ch);
}

bool isIdentifierPart(const char& ch) {
    return isIdentifierStart(ch) ||
           ch == '_';
}

bool isClearNumber(const char& ch) {
    return (isWhitespace(ch) ||
            ch == '+'  ||
            ch == ','  ||
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