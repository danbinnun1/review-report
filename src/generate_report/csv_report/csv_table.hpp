#pragma once
#include "Table.hpp"
#include "report_data.hpp"
#include <fstream>

/**
 * @brief inserts table into csv file
 * 
 * @param csv_file_stream the stream of the output file
 * @param table the table to insert
 */
void insert_csv_table(std::ofstream& csv_file_stream, const report_data& table);