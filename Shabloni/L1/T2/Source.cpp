#include <iostream>
#include "sql_query_builder.h"
#include <map>

int main() {
    SqlSelectQueryBuilder builder;

    builder.AddColumns({ "name", "phone", "age" })
        .AddFrom("students")
        .AddWhere({ {"id", "42"}, {"name", "John"}, {"age", "21"} });

    std::cout << builder.BuildQuery() << std::endl;

}
