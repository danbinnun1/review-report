#include "insert_data.hpp"
#include "DBRanking.hpp"

void report::insert_data(const std::string &report_path, const report::ReportGenerator &reportGenerator, const report_data &data)
{
    initialize_database();
    insert_new_data(data);
    std::unique_ptr<history_reports_data> history_data = get_past_data();
    reportGenerator.generate_report(report_path, *history_data);
}