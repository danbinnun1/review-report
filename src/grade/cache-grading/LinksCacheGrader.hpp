#pragma once
#include "LinksCache.hpp"
#include "SearchResultGrader.hpp"
#include <memory>
namespace grading
{
    class LinksCacheGrader : public SearchResultGrader
    {
    private:
        std::shared_ptr<LinksCache> m_cache;

    public:
        int grade(const std::vector<std::string> &links) const override;
        virtual int
        gradeInterestingLinks(const std::vector<std::string> &links) const = 0;
    };
} // namespace grading