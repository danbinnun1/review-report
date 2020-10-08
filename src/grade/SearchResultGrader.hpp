#pragma once
#include <string>
#include <vector>
namespace grading
{
    class SearchResultGrader
    {
    private:
        virtual int grade(const std::vector<std::string> &links) const = 0;
        virtual ~SearchResultGrader() = 0;
    };
} // namespace grading