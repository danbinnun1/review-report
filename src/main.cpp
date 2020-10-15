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

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include "extract_links.hpp"
using namespace grading;
int main(){
    
    //curlpp::initialize(long flags = CURL_GLOBAL_ALL);
    //cURLpp::initialize(flags = CURL_GLOBAL_ALL);
    		curlpp::Cleanup myCleanup;

    std::cout<< search::extract_links(get_html("https://www.google.com/search?q=google&oq=go&aqs=chrome.0.69i59l3j69i57j35i39j69i60l3.743j0j4&sourceid=chrome&ie=UTF-8&num=70"))[0]<<std::endl;
    //get_html("http://www.youtube.com");
   //cURLpp::terminate();
}