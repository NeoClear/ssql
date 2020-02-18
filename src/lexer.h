#pragma once

#include <string>


class lexer {
public:
    enum token {
        INTEGER,
        FLOAT,
        STRING,
        LPAREN,
        RPAREN,
        DELIMITER,
        NATURAL,
        JOIN,
        LEFT,
        RIGHT,
        INNER,
        ON,
        HAVING,
        GROUP,
        BY,
        SELECT,
        INSERT,
        INTO,
        COMMA,
        FROM,
        WHERE,
        AS,
        TIMES,
        PLUS,
        MINUS,
        DIV,
        LIKE,
        AND,
        OR,
        IN,
        NIL,
        IS,
        END,
        KEYWORD,
        UNDEFINED,
    };
public:
    std::string code;
    size_t ptr = 0;
public:
    lexer(std::string _code);
    std::pair<token, std::string> get_tok();
    bool at_end();
    char get_char();
    char get_curchar();
};
