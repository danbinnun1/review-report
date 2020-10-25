#pragma once
#include <map>
#include "Table.hpp"

template <typename Row, typename Column, typename Value>
class MapTable : public Table<Row, Column, Value>
{
private:
    std::map<std::pair<Row, Column>, Value> m_map;

public:
    Value get_value(const Row &row, const Column &column) const override;
    void set_value(const Row &row, const Column &column, Value value) override;
    std::vector<Row> get_rows() const override;
    std::vector<Column> get_columns() const override;
};
