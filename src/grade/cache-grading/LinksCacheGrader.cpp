#include "LinksCacheGrader.hpp"

int grading::LinksCacheGrader::grade(
    const std::vector<std::string> &links) const {
  uint32_t uninterestingLinks = 0;
  std::vector<std::string> interestingLinks = {};
  for (const std::string &link : links) {
    if (m_cache->linkInCache(link)) {
      ++uninterestingLinks;
    } else {
      interestingLinks.push_back(link);
    }
  }
  const int interestingLinksGrade = gradeInterestingLinks(interestingLinks);
  return (uninterestingLinks +
          interestingLinks.size() * interestingLinksGrade) /
         links.size();
}