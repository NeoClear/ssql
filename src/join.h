#pragma once
#include "table.h"

namespace ssql {
    table cross_join(table l, table r, std::string rname);
}
