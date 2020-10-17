#pragma once
#include "ReportGenerator.hpp"
#include <map>

template <class T>
    class CsvReportGenerator : public ReportGenerator <std::map<std::pair<std::string, std::string>, T>>
{

public:
    virtual void generate_report(const std::string &output_file, const std::map<std::pair<std::string, std::string>, T> &data) const = 0;
};
