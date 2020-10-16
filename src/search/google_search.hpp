#pragma once
#include <string>
#include <vector>
namespace search{
std::vector<std::string> get_google_search_results(const std::string& seach_word, const std::string& language);
}