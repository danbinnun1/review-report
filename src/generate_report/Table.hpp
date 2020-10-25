#pragma once
#include <vector>

template <class Row, class Column, class Value>
class Table
{

public:
    virtual Value get_value(const Row &row, const Column &column) const = 0;
    virtual void set_value(const Row &row, const Column &column, Value value) = 0;
    virtual std::vector<Row> get_rows() const = 0;
    virtual std::vector<Column> get_columns() const = 0;
    virtual ~Table() = default;
};
