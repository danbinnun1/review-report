#include "review_report.hpp"

#include <MapTable.hpp>
#include "google_search.hpp"
#include <unistd.h>
#include "insert_data.hpp"

void generate_review_report(const std::string &searching_data_file,
                            const std::string &report_path,
                            const data_file_parser::SearchingDataParser &parser,
                            const grading::SearchResultGrader &grader,
                            const uint32_t sleep_time,
                            const report::ReportGenerator &report_generator, std::ostream &log_stream)
{
    const auto searching_data =
        parser.get_product_languages_map(searching_data_file);
    MapTable<std::string, std::string, std::vector<std::string>> links;
    for (const auto &element : searching_data)
    {
        const std::string product = element.first;
        log_stream << "starts searching product: " << product << std::endl;
        for (const auto &language : element.second)
        {
            log_stream << "searching product :" << product << " in language: " << language << std::endl;
            links.set_value(product, language,
                            search::get_google_search_results(product, language));
            sleep(sleep_time);
        }
    }
    MapTable<std::string, std::string, std::string> grading_result;
    for (const auto &element : searching_data)
    {
        for (const auto &language : element.second)
        {
            grading_result.set_value(element.first, language,
                                     std::to_string(grader.grade(
                                         links.get_value(element.first, language))));
        }
    }
    report::insert_data(report_path, report_generator, grading_result);
}