#include "LinksCacheGrader.hpp"

grading::LinksCacheGrader::LinksCacheGrader(LinksCache *cache) : m_cache(cache) {}

double grading::LinksCacheGrader::grade(
    const std::vector<std::string> &links) const
{
    std::vector<std::string> interestingLinks = {};
    for (const std::string &link : links) {
        if (!m_cache->linkInCache(link)) {
            interestingLinks.push_back(link);
        }
    }
    const double interestingLinksGrade = gradeInterestingLinks(interestingLinks);
    return (
               interestingLinks.size() * interestingLinksGrade) /
           links.size();
}