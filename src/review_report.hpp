#pragma once

#include "SearchResultGrader.hpp"
#include "ReportGenerator.hpp"
#include "SearchingDataParser.hpp"

#include <string>
#include <iostream>

/**
 * @brief generates google search review report
 * 
 * @param searching_data_file the path of the file of the searching data, it contains verything that needs to be ranked
 * @param report_path the path for the report file to be generated
 * @param parser the parser of the searching data file
 * @param grader the grader to grade the search results
 * @param sleep_time the time in seconds to sleep between each search
 * @param report_generator the generator of the report file
 * @param log_stream the output stream for writing logs of the process
 */
void generate_review_report(const std::string &searching_data_file,
                            const std::string &report_path,
                            const data_file_parser::SearchingDataParser &parser,
                            const grading::SearchResultGrader &grader,
                            const uint32_t sleep_time,
                            const report::ReportGenerator &report_generator, std::ostream &log_stream);
                            