#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "../parser/Parser.hpp"

namespace stdlibrary {
    class Std {
    public:
        explicit Std(parser::Parser& parser);

    private:
        parser::Parser& parser;
        void sort();
        void filter();
    };

}


#endif 