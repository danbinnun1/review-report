#pragma once
#include "ReportGenerator.hpp"
#include "Table.hpp"
#include "report_data.hpp"
#include <iostream>

namespace report
{
    class CsvReportGenerator : public ReportGenerator
    {

    public:
    /**
     * @brief generates csv report
     * 
     * @param output_file the path for the report to be generated
     * @param data the data of all past weeks
     */
        void
        generate_report(const std::string &output_file,
                        const history_reports_data& data) const override;
    };
} // namespace report