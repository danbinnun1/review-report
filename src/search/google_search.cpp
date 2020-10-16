#include "google_search.hpp"

#include "get_html.hpp"
#include "extract_links.hpp"

std::vector<std::string> search::get_google_search_results(const std::string &seach_word, const std::string &language)
{
    const std::string url = "https://www.google.com/search?q=" + seach_word + "&lr=" + language;
    const std::string html_response=get_html(url);
    const auto search_links=extract_links(html_response);
    return search_links;
}