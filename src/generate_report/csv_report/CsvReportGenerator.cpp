#include "CsvReportGenerator.hpp"
#include <fstream>
#include <iostream>
#include "MapTable.hpp"
#include "csv_table.hpp"
#include <memory>

#define NO_VALUE ""

void report::CsvReportGenerator::generate_report(const std::string &output_file,
                                                 const history_reports_data &data) const
{
    std::ofstream output_stream;
    output_stream.open(output_file);

    const std::vector<std::string> products = data.get_rows();
    const std::vector<std::string> languages = data.get_columns();

    //insert last week data
    {
        const std::unique_ptr<Table<std::string, std::string, std::string>> last_data = std::make_unique<MapTable<std::string, std::string, std::string>>();
        for (const std::string &product : products) {
            for (const std::string &language : languages) {
                last_data->set_value(product, language, data.get_value(product, language).back());
            }
        }
        insert_csv_table(output_stream, *last_data);
    }
    output_stream<<"\n";

    for (const std::string &product : products) {
        output_stream<<product<<"\n";
        const std::unique_ptr<Table<std::string, std::string, std::string>> product_history_data = std::make_unique<MapTable<std::string, std::string, std::string>>();

        for (const std::string &language : languages) {
            const auto product_language_history = data.get_value(product, language);
            if (product_language_history[0] != NO_VALUE) {
                for (auto it = product_language_history.begin(); it != product_language_history.end(); ++it) {
                    const uint32_t index = std::distance(product_language_history.begin(), it);
                    //crate table with week num as row label and language as column label
                    product_history_data->set_value(std::to_string(index), language, *it);
                }
            }
        }
        insert_csv_table(output_stream, *product_history_data);
        output_stream<<"\n";
    }
}