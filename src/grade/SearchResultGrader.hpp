#pragma once
#include <string>
#include <vector>
namespace grading
{
    class SearchResultGrader
    {
    public:
        /**
         * @brief grade google search result
         * 
         * @param links the links of the google search result
         * @return double the grade
         */
        virtual double grade(const std::vector<std::string> &links) const = 0;
        virtual ~SearchResultGrader() = default;
    };
} // namespace grading