#pragma once
#include <string>
#include <vector>
namespace search{
/**
 * @brief extarcts links from google search html
 * 
 * @param google_search_html html of google search result page
 * @return std::vector<std::string> vector of links as strings
 */
std::vector<std::string> extract_links(const std::string& google_search_html);
}