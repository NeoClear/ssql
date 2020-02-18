#include "lexer.h"

lexer::lexer(std::string _code) {
    code.swap(_code);
}

std::pair<lexer::token, std::string> lexer::get_tok() {
    char ch = get_char();
    while (ch == ' ' || ch == '\b' ||
           ch == '\n' || ch == '\r')
           ch = get_char();
    if (ch == EOF)
        return {END, ""};
    std::string block;
    block += ch;
    if (isalnum(ch) || ch == '_' || ch == '.') {
        char cur = get_curchar();
        while (isalnum(cur) || cur == '_' || cur == '.') {
            block += get_char();
            cur = get_curchar();
        }
        if (block == "select")
            return {SELECT, block};
        else if (block == "from")
            return {FROM, block};
        else if (block == "where")
            return {WHERE, block};
        else if (block == "as")
            return {AS, block};
        else if (block == "like")
            return {LIKE, block};
        else if (block == "and")
            return {AND, block};
        else if (block == "or")
            return {OR, block};
        else if (block == "IN")
            return {IN, block};
        else if (block == "NIL")
            return {NIL, block};
        else if (block == "IS")
            return {IS, block};
        else
            return {KEYWORD, block};
    }
    if (ch == '(')
        return {LPAREN, "("};
    if (ch == ')')
        return {RPAREN, ")"};
    if (ch == '*')
        return {TIMES,  "*"};
    if (ch == '+')
        return {PLUS, "+"};
    if (ch == '-')
        return {MINUS, "-"};
    if (ch == '/')
        return {DIV, "/"};
    if (ch == ';')
        return {DELIMITER, ";"};
    if (ch == ',')
        return {COMMA, ","};
    
    return {UNDEFINED, ""};
}

bool lexer::at_end() {
    return ptr >= code.size();
}

char lexer::get_char() {
    if (at_end())
        return EOF;
    return code[ptr++];
}

char lexer::get_curchar() {
    if (at_end())
        return EOF;
    return code[ptr];
}
