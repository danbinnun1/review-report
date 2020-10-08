#include "WebPageGrader.hpp"


grading::WebPageGrader::WebPageGrader(URLOpener* opener, LinksCache* cache) : LinksCacheGrader(cache) , m_opener(opener) {}


double grading::WebPageGrader::gradeInterestingLinks(const std::vector<std::string> &links) const{
    return 5;
}