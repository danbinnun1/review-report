#include "extract_links.hpp"

#include <libxml/tree.h>
#include <libxml/HTMLparser.h>
#include <libxml++/libxml++.h>

std::vector<std::string> search::extract_links(const std::string &google_search_html) {
    xmlDoc *doc = htmlReadDoc((xmlChar *)google_search_html.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

    xmlNode *r = xmlDocGetRootElement(doc);
    const xmlpp::Element *const root = new xmlpp::Element(r);

    const std::string xpath = "//*[@id=\"rso\"]/div[@class=\"g\"]/div/div[1]/a";
    const auto elements = root->find(xpath);

    std::vector<std::string> search_links = {};
    for (const auto &element : elements) {
        search_links.push_back(dynamic_cast<xmlpp::Element *>(element)->get_attribute_value(std::string("href")));
    }

    delete root;
    xmlFreeDoc(doc);
    return search_links;
}