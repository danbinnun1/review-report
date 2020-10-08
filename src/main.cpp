#include "LinksTextCache.hpp"
#include "LinksCache.hpp"
#include "AskReviewType.hpp"
#include "LinuxURLOpener.hpp"
#include "URLOpener.hpp"
#include <iostream>
#include "SearchResultGrader.hpp"
#include "WebPageGrader.hpp"
using namespace grading;
int main(){
    SearchResultGrader* a= new WebPageGrader(new LinuxURLOpener(), new LinksTextCache("a.txt"));
    std::string s1="http//:youtube.com";
    std::string s2="http//:google.com";
    std::vector<std::string> b={s1, s2};
    //std::cout<<a->grade(b);
}