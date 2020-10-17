#pragma once
#include <string>
template <class T>
class ReportGenerator
{

public:
    virtual void generate_report(const std::string& output_file, const T& data) const = 0;
    virtual ~ReportGenerator() = default;
};