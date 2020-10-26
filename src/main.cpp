#include "AskReviewType.hpp"
#include "LinksCache.hpp"
#include "LinksTextCache.hpp"
#include "LinuxURLOpener.hpp"
#include "SearchResultGrader.hpp"
#include "URLOpener.hpp"
#include "WebPageGrader.hpp"
#include "get_html.hpp"
#include <iostream>
#include <string>

#include "extract_links.hpp"
#include "google_search.hpp"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
using namespace grading;
#include "CsvParser.hpp"
#include "CsvReportGenerator.hpp"
#include "MapTable.hpp"
#include "SearchingDataParser.hpp"
#include "csv_table.hpp"
#include "review_report.hpp"
#include <ctime>
#include <fstream>
#include <thread>
#include <time.h>
std::vector<std::string> a;
std::vector<std::string> c;
#define SLEEP_TIME 10
using namespace std;

void f() { a = search::get_google_search_results("hello", "lang_de"); }

std::vector<std::string> d;

void y() { d = search::get_google_search_results("israel", "lang_ar"); }

void g() { c = search::get_google_search_results("hello", "lang_iw"); }

int main(int argc, char *argv[]) {
  generate_review_report(
      "r.csv", "t.csv", data_file_parser::CsvParser(),
      grading::WebPageGrader(new grading::LinuxURLOpener(),
                             new grading::LinksTextCache("q.txt")),
      SLEEP_TIME, report::CsvReportGenerator(), std::cout);
//      auto i=data_file_parser::CsvParser();
  //  auto u=i.get_product_languages_map("r.csv");
    //  for (auto e:u){
      //    cout<<e.first[5]<<std::endl;
      //}
      //cout<<u.get_product_languages_map("r.csv").at("pizza").size();
}