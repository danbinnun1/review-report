#include "LinksTextCache.hpp"
#include "LinksCache.hpp"
#include "AskReviewType.hpp"
#include "LinuxURLOpener.hpp"
#include "URLOpener.hpp"
#include <iostream>
#include "SearchResultGrader.hpp"
#include "WebPageGrader.hpp"
#include "get_html.hpp"
#include <iostream>
using namespace grading;
int main(){
    std::cout<< get_html("http://www.google.com")<<std::endl;
    get_html("htttp://www.youtube.com");
}