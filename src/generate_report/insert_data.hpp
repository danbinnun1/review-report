#pragma once
#include "ReportGenerator.hpp"
#include <string>
#include "Table.hpp"
#include "report_data.hpp"

namespace report{
/**
 * @brief recieves new data, saves it and generates a report using this and past data
 * 
 * @param report_path the path where the report will be generated
 * @param reportGenerator the generator of the report
 * @param data the new data
 */
void insert_data(const std::string& report_path, const report::ReportGenerator& reportGenerator, const report_data& data);
}