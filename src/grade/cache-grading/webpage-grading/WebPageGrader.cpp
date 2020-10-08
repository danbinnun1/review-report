#include "WebPageGrader.hpp"
#include "ReviewType.hpp"
#include "AskReviewType.hpp"

grading::WebPageGrader::WebPageGrader(URLOpener *opener, LinksCache *cache) : LinksCacheGrader(cache), m_opener(opener) {}

double grading::WebPageGrader::gradeInterestingLinks(const std::vector<std::string> &links) const {
    uint32_t badReviews = 0;
    uint16_t notBadReviews = 0;
    for (const std::string &link : links) {
        m_opener->openLink(link);
        ReviewType reviewType = askUser();
        if (reviewType == ReviewType::BAD) {
            ++badReviews;
        }
        else if (reviewType == ReviewType::NOT_BAD) {
            ++notBadReviews;
        }
        else if (reviewType == ReviewType::UNINTERESTING) {
            m_cache->insertLink(link);
            ++notBadReviews;
        }
    }
    return badReviews / (badReviews + notBadReviews);
}