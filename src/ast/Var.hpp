#ifndef PARSER_VAR_HPP_
#define PARSER_VAR_HPP_

#include "VarType.hpp"
#include <vector>
#include <iostream>
#include <sstream>

typedef int possibleValue;
typedef std::vector<possibleValue> valueVec;

namespace ast
{

class Var
{
public:
    Var() :
        type(VarType::UNDEFINED), value({}) {}

    Var(VarType type_, valueVec value_) :
        type(type_), value(value_) {}
    
    Var(Var&& rval) : value(std::move(rval.value)) {}


    Var& operator =(const Var& rval) = default;
    Var(const Var&) = default;

    VarType getDataType() { return type; }
    valueVec getValue() { return value; }
    void setDataType(VarType type_) { type = type_; }
    void setValue(valueVec val_) { value = val_; }

    void print() {
        switch(type){
            case VarType::INT:
                std::cout << "INT\n"; break;
            default:
                break;
        }
    }
    int& operator[](int idx);
    const int& operator[](int idx) const;
    std::vector<int>& operator*();

    Var operator==(const Var &rval) const;
    Var operator!=(const Var &rval) const;

    Var operator<(const Var &rval) const;
    Var operator>(const Var &rval) const;
    Var operator<=(const Var &rval) const;
    Var operator>=(const Var &rval) const;

    Var operator+() const;
    Var operator-() const;

    Var operator+(const Var &rval) const;
    Var operator-(const Var &rval) const;
    Var operator*(const Var &rval) const;
    Var operator/(const Var &rval) const;
    Var operator%(const Var &rval) const;

    Var operator!() const;
    Var operator&&(const Var &rval) const;
    Var operator||(const Var &rval) const;

    explicit operator bool() const;

    friend std::ostream &operator<<(std::ostream &os, const Var &variable);
    const std::string toString() const;

    int& at(unsigned idx);
    const int& at(unsigned idx) const;
    unsigned int size();
    VarType type;
    valueVec value;

private:

    Var vTrue() const {
        return Var(VarType::INT, std::vector<int>(1, 1));
    }
    Var vFalse() const {
        return Var();
    }
};


inline std::ostream &operator<<(std::ostream &os, const Var &variable) {
    os << "(";
    for (unsigned int i = 0; i < variable.value.size(); ++i) {
        os << variable.value[i];
        if(i < variable.value.size() - 1)
            os << ",";
    }
    os << ")";
    return os;

}

}

#endif