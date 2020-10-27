#pragma once
#include <string>
#include <vector>
namespace search{
/**
 * @brief serach word in google by language
 * 
 * @param seach_word the senetence to search
 * @param language the language to search with
 * @return std::vector<std::string> vector of links of the search result
 */
std::vector<std::string> get_google_search_results(const std::string& seach_word, const std::string& language);
}