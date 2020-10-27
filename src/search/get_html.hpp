#pragma once
#include <string>
namespace search{
/**
 * @brief sends GEt http request and returns result
 * 
 * @param url the url of the request
 * @return std::string response body
 */
std::string get_html(const std::string& url);
}