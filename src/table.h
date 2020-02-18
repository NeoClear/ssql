#pragma once

#include <vector>
#include <string>
#include <variant>

class table {
public:
    enum attr_dom {
        integer,
        string,
    };
    struct attr {
        std::string name;
        attr_dom domain;
    };
public:
    std::vector<attr> schema;
    std::vector<std::vector<std::variant<int, std::string>>> relation;
public:
    table();
    table(std::vector<attr> _schema);
    ~table();
    void insert(std::vector<std::variant<int, std::string>> _entry);
    int get_attr_id(std::string name);
    void print();
};
