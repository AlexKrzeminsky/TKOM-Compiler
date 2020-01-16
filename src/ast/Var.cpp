#include "Var.hpp"

using namespace ast;

int &Var::operator[](int idx) {
    return value[idx];
}

const int &Var::operator[](int idx) const {
    return value[idx];
}

std::vector<int> &Var::operator*() {
    return value;
}

Var Var::operator==(const Var &rval) const {
    if (value == rval.value) {
        return vTrue();
    } else {
        return vFalse();
    }
}

Var Var::operator!=(const Var &rval) const {
    return !(rval == *this);
}

Var Var::operator<(const Var &rval) const {
    if (value < rval.value) {
        return vTrue();
    } else {
        return vFalse();
    }
}

Var Var::operator>(const Var &rval) const {
    return rval < *this;
}

Var Var::operator<=(const Var &rval) const {
    return !(rval < *this);
}

Var Var::operator>=(const Var &rval) const {
    return !(*this < rval);
}

Var Var::operator+() const {
    return *this;
}

Var Var::operator-() const {
    Var var(VarType::INT, std::vector<int>(value.size()));
    for (unsigned int i = 0; i < value.size(); ++i) {
        var[i] = -value[i];
    }
    return var;
}

Var Var::operator+(const Var &rval) const {
    Var var;
    if (value.size() == rval.value.size()) {
        var = *this;
        for (unsigned int i = 0; i < value.size(); ++i) {
            var[i] += rval.value[i];
        }
    } else {
        throw std::runtime_error("Cant add two vectors with different size");
    }

    return var;
}

Var Var::operator-(const Var &rval) const {
    Var var;
    if (value.size() == rval.value.size()) {
        var = *this;
        for (unsigned int i = 0; i < value.size(); ++i) {
            var[i] -= rval.value[i];
        }
    } else {
        throw std::runtime_error("Cant subtract two vectors with different size");
    }

    return var;
}

Var Var::operator*(const Var &rval) const {
    Var var;
    if (value.size() == 1) {
        var = rval;
        for (auto &variable : var.value) {
            variable *= value[0];
        }
    } else if (rval.value.size() == 1) {
        var = *this;
        for (auto &variable : var.value) {
            variable *= rval.value[0];
        }
    } else {
        throw std::runtime_error("Cant multiply vectors if they both contain more than 1 value");
    }

    return var;
}

Var Var::operator/(const Var &rval) const {
    Var var;
    if (rval.value.size() == 1) {
        var = *this;
        for (auto &variable : var.value) {
            if(rval.value[0]) {
                variable /= rval.value[0];
            } else {
                throw std::runtime_error("Cannot divide by 0");
            }
        }
    } else {
        throw std::runtime_error("vector dividing must be of size 1");
    }

    return var;
}

Var Var::operator%(const Var &rval) const {
    Var var;
    if (rval.value.size() == 1) {
        var = *this;
        for (auto &variable : var.value) {
            if(rval.value[0]) {
                variable %= rval.value[0];
            } else {
                throw std::runtime_error("Cannot modulo by 0");
            }
        }
    } else {
        throw std::runtime_error("vector doing modulo must be of size 1");
    }

    return var;
}

Var::operator bool() const {
    return !value.empty();
}

Var Var::operator!() const {
    if (*this) {
        return vFalse();
    } else {
        return vTrue();
    }
}

Var Var::operator&&(const Var &rval) const {
    if (static_cast<bool>(*this) && static_cast<bool>(rval)) {
        return vTrue();
    } else {
        return vFalse();
    }
}

Var Var::operator||(const Var &rval) const {
    if (static_cast<bool>(*this) || static_cast<bool>(rval)) {
        return vTrue();
    } else {
        return vFalse();
    }
}

unsigned int Var::size() {
    return value.size();
}

int &Var::at(unsigned idx) {
    // >= 0 checked because of unsigned IDX
    if (idx < value.size()) {
        return value.at(idx);
    } else {
        throw std::runtime_error("Index out of range");
    }
}

const int &Var::at(unsigned idx) const {
    // >= 0 checked because of unsigned IDX
    if (idx < value.size()) {
        return value.at(idx);
    } else {
        throw std::runtime_error("Index out of range");
    }
}

const std::string Var::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}