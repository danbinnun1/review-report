#pragma once
#include "Table.hpp"
#include <string>
#include <vector>

//data for one time
typedef Table<std::string, std::string, std::string> report_data;

//data for all past times
typedef Table<std::string, std::string, std::vector<std::string>> history_reports_data;