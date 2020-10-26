#pragma once
#include <string>
#include <vector>
#include "Table.hpp"
#include <memory>
#include "report_data.hpp"

#define DATABASE_PATH "a"

/**
 * @brief initializes new sqlite file. if it alreadt exists it does nothing
 * 
 * @param filepath the path of the file
 */
void initialize_database();

/**
 * @brief Get the past data from the database
 * 
 * @param filepath darabase filepath
 * @return table of products rows, languages columns, and the ratings the product in the language in the value,
 * if value is blank it means there is no data for it
 */
std::unique_ptr<history_reports_data> get_past_data();

/**
 * @brief insert new data to database
 * 
 * @param data table that maps between product and language to value, if there is no value it should be blank
 * @param filepath database file path
 */
void insert_new_data(const Table<std::string, std::string, std::string>& data);