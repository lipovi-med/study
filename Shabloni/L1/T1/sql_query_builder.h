#pragma once
#include <string>
#include <vector>
#include <sstream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> where_conditions;

public:
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
        table = table_name;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions.emplace_back(column, value);
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;

        if (columns.empty()) {
            query << "SELECT * ";
        }
        else {
            query << "SELECT ";
            for (size_t i = 0; i < columns.size(); ++i) {
                query << columns[i];
                if (i + 1 != columns.size()) query << ", ";
            }
            query << " ";
        }

        if (!table.empty()) {
            query << "FROM " << table << " ";
        }

        if (!where_conditions.empty()) {
            query << "WHERE ";
            for (size_t i = 0; i < where_conditions.size(); ++i) {
                query << where_conditions[i].first << "=" << where_conditions[i].second;
                if (i + 1 != where_conditions.size()) query << " AND ";
            }
            query << " ";
        }

        query << ";";

        return query.str();
    }
};
#pragma once
