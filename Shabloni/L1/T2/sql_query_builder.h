#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string table;
    std::vector<std::pair<std::string, std::string>> where_conditions;

public:
    // Добавление одной колонки
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    // Добавление нескольких колонок
    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& cols) noexcept {
        columns.insert(columns.end(), cols.begin(), cols.end());
        return *this;
    }

    // Установка таблицы
    SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
        table = table_name;
        return *this;
    }

    // Добавление одного условия
    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions.emplace_back(column, value);
        return *this;
    }

    // Добавление нескольких условий через std::map
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [col, val] : kv) {
            where_conditions.emplace_back(col, val);
        }
        return *this;
    }

    // Построение запроса
    std::string BuildQuery() const {
        std::ostringstream query;

        // SELECT
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

        // FROM
        if (!table.empty()) {
            query << "FROM " << table << " ";
        }

        // WHERE
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
