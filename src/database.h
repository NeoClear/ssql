#pragma once

#include <unordered_map>
#include "table.h"
#include "lexer.h"

class db {
public:
    std::unordered_map<std::string, table> tables;
    void insert(std::string name, table _table);
    table parse(std::string code);
    table select(std::vector<std::pair<lexer::token, std::string>> tokens, table _table);
    table from(std::vector<std::pair<lexer::token, std::string>> tokens);
};
