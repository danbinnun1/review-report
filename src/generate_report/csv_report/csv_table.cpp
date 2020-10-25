#include "csv_table.hpp"

#define COMMA ","
#define NEWLINE "\n"

void insert_csv_table(std::ofstream& csv_file_stream, const report_data& table){
    const auto rows=table.get_rows();
    const auto columns=table.get_columns();
    for (const std::string& column:columns ){
        csv_file_stream<<COMMA<<column;
    }
    csv_file_stream<<NEWLINE;
    for (const std::string& row:rows){
        csv_file_stream<<row;
        for (const std::string& column:columns){
            csv_file_stream<<COMMA<<table.get_value(row, column);
        }
        csv_file_stream<<NEWLINE;
    }
}