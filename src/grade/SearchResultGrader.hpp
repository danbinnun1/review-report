#pragma once
#include <string>
#include <vector>
namespace grading
{
    class SearchResultGrader
    {
    public:
        virtual double grade(const std::vector<std::string> &links) const = 0;
        virtual ~SearchResultGrader() = default;
    };
} // namespace grading