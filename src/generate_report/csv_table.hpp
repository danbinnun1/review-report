#pragma once
#include "Table.hpp"
#include <fstream>

void insert_csv_table(std::ofstream& csv_file_stream, const Table<std::string, std::string, std::string>& table);