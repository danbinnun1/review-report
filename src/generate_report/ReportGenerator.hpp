#pragma once
#include "Table.hpp"
#include <string>
#include <vector>
namespace report
{
    class ReportGenerator
    {

    public:
        /**
     * @brief generates review report
     * 
     * @param output_file output file path for the report to be 
     * @param data data of the report to be processed
     */
        virtual void
        generate_report(const std::string &output_file,
                        const Table<std::string, std::string, std::vector<std::string>>& data) const = 0;
        virtual ~ReportGenerator() = default;
    };
} // namespace report