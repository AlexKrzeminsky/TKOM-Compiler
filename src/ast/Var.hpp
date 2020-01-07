#ifndef PARSER_VAR_HPP_
#define PARSER_VAR_HPP_

#include "VarType.hpp"
#include <iostream>

typedef int possibleValue;
typedef std::vector<possibleValue> valueVec;

class Var
{
public:
    Var() :
        type(VarType::UNDEFINED), value({}) {}
    Var(VarType type_, valueVec value_) :
        type(type_), value(value_) {}
    
    VarType getDataType() { return type; }
    valueVec getValue() { return value; }
    void setDataType(VarType type_) { type = type_; }
    void setValue(valueVec val_) { value = val_; }

    void print() {
        switch(type){
            case VarType::INT:
                std::cout << "INT\n"; break;
            case VarType::FLOAT:
                std::cout << "FLOAT\n"; break;
            case VarType::STRING:
                std::cout << "STRING\n"; break;
            case VarType::LIST:
                std::cout << "LIST\n"; break;
            default:
                break;
        }
    }

private:
    VarType type;
    valueVec value;
};

#endif