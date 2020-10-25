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
#include "MapTable.hpp"
#include "csv_table.hpp"
#include <fstream>
std::vector<std::string> a;
std::vector<std::string> c;
using namespace std;

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
    MapTable<std::string,std::string,std::string> t=MapTable<std::string,std::string,std::string>();
    t.set_value("1","a","hello");
    t.set_value("row","col","kaki");
    t.set_value("1", "col","k");
    t.set_value("row", "a","i");
    //cout<<t.get_value("1","a")<<t.get_columns()[0]<<t.get_rows()[0];
    ofstream f;
    f.open("a.csv");
    insert_csv_table(f,t);
}