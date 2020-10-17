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
#include <thread>
#include <ctime>
#include <time.h>
#include "SearchingDataParser.hpp"
#include "CsvParser.hpp"
std::vector<std::string> a;
std::vector<std::string> c;

void f()
{
    a = search::get_google_search_results("hello", "lang_de");
}

std::vector<std::string> d;

void y()
{
    d = search::get_google_search_results("israel", "lang_ar");
}

void g()
{
    c = search::get_google_search_results("hello", "lang_iw");
}

int main(int argc, char *argv[])
{

    //curlpp::initialize(long flags = CURL_GLOBAL_ALL);
    //cURLpp::initialize(flags = CURL_GLOBAL_ALL);
    curlpp::Cleanup myCleanup;
    //std::cout<<get_html("https://www.google.com/search?q=" + std::string(argv[1]))<<std::endl;
    //auto a= search::get_google_search_results("hello","lang_de");//+ "&num=" + std::string(argv[2])));
    //const clock_t begin_time = clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    std::thread t(f);
    std::thread r(g);
    std::thread u(y);
    t.join();
    u.join();
    r.join();

    //   f();
    // g();
    for (auto b : a)
    {
        std::cout << b << std::endl;
    }
    std::cout << std::endl;
    for (auto b : c)
    {
        std::cout << b << std::endl;
    }
    std::cout<<std::endl;
    for (auto b : d)
    {
        std::cout << b << std::endl;
    }
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << elapsed_time_ms / 1000 << std::endl;
    //get_html("http://www.youtube.com");
    //cURLpp::terminate();
    data_file_parser::CsvParser p;
    const auto e=p.get_product_languages_map("./example.csv");
    for (const auto& x:e ){
        std::cout<<x.first<<std::endl;
        for (auto i:x.second){
            std::cout<<"kkk"<<i<<std::endl;
        }
    }
}