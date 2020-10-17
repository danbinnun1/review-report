#pragma once
#include "SearchingDataParser.hpp"

namespace data_file_parser
{
    class CsvParser : public SearchingDataParser
    {

    public:
        std::map<std::string, std::vector<std::string>> get_product_languages_map(const std::string &file_name) const override;
    };

} // namespace data_file_parser