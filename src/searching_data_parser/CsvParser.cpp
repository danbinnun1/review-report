#include "CsvParser.hpp"
#include <iostream>

#include "file_reading.hpp"
#include "split.hpp"

#define HAS_LANGUAGE "X"

std::map<std::string, std::vector<std::string>> data_file_parser::CsvParser::get_product_languages_map(const std::string &file_name) const
{
    //read csv content and split to rows
    const std::string content = readFileContent(file_name);
    const auto rows = splitByDelimiter(content.c_str(), '\n');
    const auto products = splitByDelimiter(rows[0].c_str(), ',');

    std::map<std::string, std::vector<std::string>> product_languages_map;
    for (auto product = products.begin() + 1; product != products.end(); product++) {
        product_languages_map.insert(std::pair<std::string, std::vector<std::string>>(*product, std::vector<std::string>()));
    }

    for (auto row = rows.begin()+1; row != rows.end(); ++row) {
        const auto values = splitByDelimiter((*row).c_str(), ',');
        const auto language = values[0];
        for (size_t i = 1; i < products.size(); ++i) {
            if (values[i] == HAS_LANGUAGE) {
                product_languages_map.at(products[i]).push_back(language);
            }
        }
    }
    return product_languages_map;
}
