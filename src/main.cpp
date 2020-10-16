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
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "google_search.hpp"
#include "extract_links.hpp"
using namespace grading;
int main(int argc, char *argv[]){
    
    //curlpp::initialize(long flags = CURL_GLOBAL_ALL);
    //cURLpp::initialize(flags = CURL_GLOBAL_ALL);
    		curlpp::Cleanup myCleanup;
    //std::cout<<get_html("https://www.google.com/search?q=" + std::string(argv[1]))<<std::endl;
    auto a= search::get_google_search_results("hello","lang_de");//+ "&num=" + std::string(argv[2])));
    for (auto b:a){
        std::cout<<b<<std::endl;
    }
    //get_html("http://www.youtube.com");
   //cURLpp::terminate();
}