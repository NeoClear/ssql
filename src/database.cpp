#include "database.h"
#include "lexer.h"
#include "unordered_set"
#include "join.h"
#include <iostream>
#include <stdio.h>
#include <vector>

void db::insert(std::string name, table _table) {
    if (tables.count(name))
        throw "Table already exists!";
    tables[name] = _table;
}



table db::parse(std::string code) {
    lexer lex(code);
    std::unordered_map<lexer::token, std::vector<std::pair<lexer::token, std::string>>> tokens;
    std::pair<lexer::token, std::string> tok;
    tok = lex.get_tok();
    std::unordered_set<lexer::token> clause = {
        lexer::SELECT,
        lexer::FROM,
        lexer::WHERE,
        lexer::INSERT,
        lexer::GROUP,
        lexer::HAVING,
    };
    lexer::token category;
    while (tok.first != lexer::DELIMITER) {
        // std::cout << tok.first << std::endl;
        category = clause.count(tok.first) ? tok.first : category;
        tokens[category].push_back(tok);
        tok = lex.get_tok();
    }
    if (tokens.count(lexer::SELECT)) {
        table _table = from(tokens[lexer::FROM]);
        return select(tokens[lexer::SELECT], _table);
    }
}

table db::select(std::vector<std::pair<lexer::token, std::string>> tokens, table _table) {
    size_t ptr = 1;
    std::vector<std::pair<std::string, int>> selected;
    while (ptr < tokens.size()) {
        if (_table.get_attr_id(tokens[ptr].second) == -1)
            throw "Cannot find attribute";
        // std::cout << tokens.size() << std::endl;
        selected.push_back({tokens[ptr].second, _table.get_attr_id(tokens[ptr].second)});
        ptr++;
        if (ptr < tokens.size() && tokens[ptr].first == lexer::KEYWORD)
            selected.back().first = tokens[ptr++].second;
        if (ptr < tokens.size() && tokens[ptr].first == lexer::COMMA)
            ptr++;
    }
    std::vector<table::attr> schema;
    for (const auto& it : selected)
        schema.push_back({it.first, _table.schema[it.second].domain});
    table ans(schema);
    for (const auto entry : _table.relation) {
        std::vector<std::variant<int, std::string>> line;
        for (const auto& ele : selected)
            line.push_back(entry[ele.second]);
        ans.relation.push_back(line);
    }
    return ans;
}

table db::from(std::vector<std::pair<lexer::token, std::string>> tokens) {
    size_t ptr = 1;
    table ans;
    ans.relation.push_back({});
    // for (const auto& it : tokens)
    //     std::cout << it.second << " ";
    enum join {
        CROSS_JOIN,
        NATURAL_JOIN,
        INNER_JOIN,
        LEFT_JOIN,
        RIGHT_JOIN,
        OUTER_JOIN,
    };
    join join_type = CROSS_JOIN;

    while (ptr < tokens.size()) {
        // if it is the name of a table
        if (tokens[ptr].first == lexer::KEYWORD) {
            if (!tables.count(tokens[ptr].second))
                throw "Unable to find table";
            table cur = tables[tokens[ptr++].second];
            std::string rename;
            if (ptr < tokens.size() && tokens[ptr].first == lexer::KEYWORD)
                rename = tokens[ptr++].second;
            switch (join_type) {
            case CROSS_JOIN:
                if (ans.relation.empty())
                    ans = cur;
                ans = ssql::cross_join(ans, cur, rename);
                break;
            }
            
        } else if (tokens[ptr++].first == lexer::COMMA) {
            // if it is comma
            join_type = CROSS_JOIN;
        }
    }
    return ans;
}
