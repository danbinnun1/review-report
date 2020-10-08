#pragma once
#include "LinksCache.hpp"
#include "SearchResultGrader.hpp"
#include <memory>
namespace grading
{
    class LinksCacheGrader : public SearchResultGrader
    {
    protected:
        LinksCache* m_cache;

    public:
        LinksCacheGrader(LinksCache* cache);
        double grade(const std::vector<std::string> &links) const override;
        virtual double
        gradeInterestingLinks(const std::vector<std::string> &links) const = 0;
        virtual ~LinksCacheGrader() = default;
    };
}