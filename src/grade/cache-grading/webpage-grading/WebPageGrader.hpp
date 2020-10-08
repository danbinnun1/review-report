#pragma once
#include "LinksCacheGrader.hpp"
#include "URLOpener.hpp"
#include "LinksCache.hpp"
namespace grading
{
    class WebPageGrader : public LinksCacheGrader
    {
    private:
        URLOpener *m_opener;

    public:
        WebPageGrader(URLOpener* opener, LinksCache* cache);
        double gradeInterestingLinks(const std::vector<std::string> &links) const override;
    };
} // namespace grading