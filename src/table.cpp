#include "table.h"
#include <iostream>

table::table() {}

table::table(std::vector<attr> _schema) {
    this->schema.swap(_schema);
}

table::~table() {}

void table::insert(std::vector<std::variant<int, std::string>> _entry) {
    this->relation.push_back(_entry);
}

int table::get_attr_id(std::string name) {
    for (int i = 0; i < schema.size(); i++) {
        std::string sname = schema[i].name;
        std::string sub;
        if (sname.find('.') != sname.npos)
            sub = sname.substr(sname.find('.') + 1, sname.length() - sname.find('.') - 1);
        if (sname == name || sub == name)
            return i;
    }
    return -1;
}

void table::print() {
    for (const auto& it : schema)
        std::cout << it.name << "|";
    std::cout << std::endl;
    for (const auto& entry : relation) {
        for (int i = 0; i < schema.size(); i++) {
            switch (schema[i].domain) {
            case attr_dom::integer:
                std::cout << std::get<int>(entry[i]) << "|";
                break;
            case attr_dom::string:
                std::cout << std::get<std::string>(entry[i]) << "|";
            }
        }
        std::cout << std::endl;
    }
}
