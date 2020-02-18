#include <iostream>
#include "src/table.h"
#include "src/lexer.h"
#include "src/database.h"

using namespace std;

int main() {
    table employee({
        {"id", table::integer},
        {"ename", table::string}
    });
    employee.insert({0, "Anya Tafliovich"});
    employee.insert({1, "Brian Harrington"});
    employee.insert({2, "Nick Cheng"});
    // employee.print();

    db dat;
    dat.insert("Employee", employee);

    // lexer lex("select * from Employee;");
    // std::pair<lexer::token, std::string> tok;
    // while ((tok = lex.get_tok()).first != lexer::END) {
    //     cout << tok.second << endl;
    // }
    try {
        dat.parse("select E1.id n1, E2.ename n2 from Employee E1, Employee E2, Employee E3;").print();
    } catch (string s) {
        cout << s << endl;
    }
    
    return 0;
}
