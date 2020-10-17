#pragma once
#include <map>
#include <vector>
#include <string>

namespace data_file_parser
{
    class SearchingDataParser
    {

    public:
        virtual std::map<std::string, std::vector<std::string>> get_product_languages_map(const std::string &file_name) const = 0;
        virtual ~SearchingDataParser() = default;
    };
} // namespace data_file_parser