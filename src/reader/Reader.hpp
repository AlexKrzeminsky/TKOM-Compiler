#ifndef READER_HPP_
#define READER_HPP_

#include <istream>
#include <memory>

class Reader {
public:
    explicit Reader(std::istream &istream);

    Reader(const Reader &) = delete;
    const Reader &operator=(const Reader &) = delete;

    char get();
    char peek();
    bool eof();

private:
    std::istream &istream;
    char sign = 0;
};

#endif