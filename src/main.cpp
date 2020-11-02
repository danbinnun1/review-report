#include <iostream>
#include "review_report.hpp"
#include "CsvParser.hpp"
#include "CsvReportGenerator.hpp"
#include "WebPageGrader.hpp"
#include "LinuxURLOpener.hpp"
#include "LinksTextCache.hpp"
#include <memory>

#define SEARCHING_DATA_FILE "r.csv"
#define REPORT_PATH "report.csv"
#define CACHE_PATH "q.txt"
#define SLEEP_TIME 10

int main(){
    std::unique_ptr<grading::URLOpener> opener=std::make_unique<grading::LinuxURLOpener>();
    std::unique_ptr<grading::LinksCache> cache=std::make_unique<grading::LinksTextCache>(CACHE_PATH);
    std::unique_ptr<grading::SearchResultGrader> grader=std::make_unique<grading::WebPageGrader>(opener.get(),cache.get());
    std::unique_ptr<data_file_parser::SearchingDataParser> parser=std::make_unique<data_file_parser::CsvParser>();
    std::unique_ptr<report::ReportGenerator> report_generator=std::make_unique<report::CsvReportGenerator>();
    generate_review_report(SEARCHING_DATA_FILE,REPORT_PATH,*parser,*grader,SLEEP_TIME,*report_generator,std::cout);

}