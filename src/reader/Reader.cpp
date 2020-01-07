#include "Reader.hpp"

#include <utility>

Reader::Reader(std::istream &istream_)
        : istream(istream_) {}

char Reader::get() {
    istream.get(sign);
    return sign;
}

char Reader::peek() {
    return static_cast<char>(istream.peek());
}

bool Reader::eof() {
    return istream.eof();
}