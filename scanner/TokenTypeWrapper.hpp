#ifndef SCANNER_TOKENTYPE_WRAPPER_H_
#define SCANNER_TOKENTYPE_WRAPPER_H_

#include <map>
#include <string>
//#include <boost/thread/mutex.hpp>
#include "TokenType.hpp"

namespace scanner 
{

/*struct Lock {
    Lock(boost::mutex& m) : m_(m) { m_.lock(); }
    ~Lock() { m_.unlock(); }
    boost::mutex& m_;
};*/

class TokenTypeWrapper
{
public:
    static TokenTypeWrapper& getInstance();

    static std::string typeToString(TokenType);
    static TokenType stringToType(std::string);

private:
    TokenTypeWrapper() {}
    TokenTypeWrapper(const TokenTypeWrapper&) = delete;
    TokenTypeWrapper& operator=(const TokenTypeWrapper&) = delete;

    typedef std::map<TokenType, std::string> TSMap_;
    typedef std::map<std::string, TokenType> STMap_;
    
    static TSMap_ reverseMap(STMap_ stmap) {
        TSMap_ result;

        for (auto &i: stmap) {
            result[i.second] = i.first;
        }

        return result;
    };

    // maps without Identifiers and Literals for string <-> token conversion
    static STMap_ stringTokenMap;
    static TSMap_ tokenStringMap;
    static TokenTypeWrapper* instance_;
};

}

#endif