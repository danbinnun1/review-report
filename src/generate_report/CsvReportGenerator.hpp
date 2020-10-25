#pragma once
#include "ReportGenerator.hpp"
#include "Table.hpp"
#include <iostream>

namespace report
{
    class CsvReportGenerator : public ReportGenerator
    {

    public:
        void
        generate_report(const std::string &output_file,
                        const Table<std::string, std::string, std::vector<std::string>>& data) const override;
    };
} // namespace report