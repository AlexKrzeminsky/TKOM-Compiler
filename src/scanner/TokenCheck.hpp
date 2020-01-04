#ifndef SCANNER_TOKENCHECK_H_
#define SCANNER_TOKENCHECK_H_

#include <string>

bool isDigit(const char&);
bool isLineBreak(const char&);
bool isWhitespace(const char&);
bool isIdentifierStart(const char&);
bool isIdentifierPart(const char&);
bool isClearIdentifier(const char&);
bool isClearNumber(const char&);
bool isFloat(const std::string&);

#endif
