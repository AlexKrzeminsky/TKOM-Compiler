#include "Std.hpp"

#include <sstream>
#include <string>

using namespace stdlibrary;

Std::Std(parser::Parser &parser) : parser(parser) {
    sort();
    filter();
}


void Std::sort() {
    std::string str = " ";
    std::stringstream sstr(str);
    parser.setScr(std::make_unique<scanner::Scanner>(sstr));
    sstr << "fun sort(arr) {\n"
                "var length = len(arr);\n"
                "var i = 0;\n"
                "var j = 0;\n"
                "var k = 0;\n"
                "var tmp = 0;\n"

                "while ( i < length ) {\n"
                "    while ( j < (length - i - 1)) {\n"
                "        if ( arr[j] > arr[j+1] ) {\n"
                "            tmp = arr[j];\n"
                "            arr[j] = arr[j+1];\n"
                "            arr[j+1] = tmp;\n"
                "        }\n"
                "        j = j + 1;\n"
                "    }\n"
                "    i = i + 1;\n"
                "    j = 0;\n"
                "}\n"
                "return arr;\n"
            "}\n";
    parser.parse();
    parser.clearScr();
}

void Std::filter() {
    std::string str = " ";
    std::stringstream sstr(str);
    parser.setScr(std::make_unique<scanner::Scanner>(sstr));
    sstr << "fun filter(arr, where, isgreater) {\n"
                "var length = len(arr);\n"
                "var i = 0;\n"
                "var new = 0;\n"
                "var newLength = 1;\n"
                "var v = 0;\n"
                "while ( i < length ) {\n"
                "    if (isgreater == 0) {\n"
                "        if (arr[i] <= 5) {\n"
                "            v = arr[i];\n"
                "            append(v, new);\n"
                "            newLength = newLength + 1;\n"
                "        }\n"
                "    }\n"
                "    else {\n"
                "        if (arr[i] >= 5) {\n"
                "            v = arr[i];\n"
                "            append(v, new);\n"
                "            newLength = newLength + 1;\n"
                "        }\n"
                "    }\n"
                "    i = i + 1;\n"
                "}\n"
                "return new[1:newLength];\n"
            "}\n";
    parser.parse();
    parser.clearScr();
}
