#include "scanner.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string ssql::read_file(std::string filename) {
    std::ifstream file;
    file.open(filename);

    std::stringstream sstr;
    sstr << file.rdbuf();
    std::string str = sstr.str();
    return str;
}

std::string ssql::read_line() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}
