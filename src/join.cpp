#include "join.h"
#include <vector>
#include <iostream>

table ssql::cross_join(table l, table r, std::string rname) {
    std::vector<table::attr> schema;
    for (const auto& it : l.schema)
        schema.push_back(it);

    for (const auto& it : r.schema) {
        schema.push_back({rname + "." + it.name, it.domain});
    }
    table _table(schema);
    for (const auto left : l.relation) {
        for (const auto right : r.relation) {
            std::vector<std::variant<int, std::string>> entry;
            entry.insert(entry.end(), left.begin(), left.end());
            entry.insert(entry.end(), right.begin(), right.end());
            _table.insert(entry);
        }
    }
    return _table;
}
