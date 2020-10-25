#include "MapTable.hpp"
#include <algorithm>

template <typename Row, typename Column, typename Value>
Value MapTable<Row, Column, Value>::get_value(const Row &row, const Column &column) const {
    return m_map.at(std::make_pair(row, column));
}

template <typename Row, typename Column, typename Value>
void MapTable<Row, Column, Value>::set_value(const Row &row, const Column &column, Value value) {
    m_map.insert(std::make_pair(std::make_pair(row, column), value));
}

template <typename Row, typename Column, typename Value>
std::vector<Row> MapTable<Row, Column, Value>::get_rows() const {
    std::vector<std::string> rows={};
    for (const auto& element:m_map){
        if (std::find(rows.begin(), rows.end(), element.first.first)==rows.end()){
            rows.push_back(element.first.first);
        }
    }
    return rows;
}

template <typename Row, typename Column, typename Value>
std::vector<Column> MapTable<Row, Column, Value>::get_columns() const {
    std::vector<std::string> cols={};
    for (const auto& element:m_map){
        if (std::find(cols.begin(), cols.end(), element.first.second)==cols.end()){
            cols.push_back(element.first.second);
        }
    }
    return cols;
}

template class MapTable<std::string,std::string,std::string>;