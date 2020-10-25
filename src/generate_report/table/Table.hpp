#pragma once
#include <vector>

template <class Row, class Column, class Value>
class Table
{

public:
    /**
     * @brief Get the value of the table
     * 
     * @param row the row of the wanted value
     * @param column the column of the wanted value
     * @return Value of the table by the row and column
     */
    virtual Value get_value(const Row &row, const Column &column) const = 0;
    /**
     * @brief Set value in the table
     * 
     * @param row the row of the wanted square
     * @param column the column of the wanted square
     * @param value the value to be set
     */
    virtual void set_value(const Row &row, const Column &column, Value value) = 0;
    /**
     * @brief Get the rows labels of the table
     * 
     * @return std::vector<Row> vector of row labels
     */
    virtual std::vector<Row> get_rows() const = 0;
    /**
     * @brief Get the columns labels of the table
     * 
     * @return std::vector<Column> vector of column labels
     */
    virtual std::vector<Column> get_columns() const = 0;
    virtual ~Table() = default;
};
