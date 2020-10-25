#pragma once
#include <string>
#include <vector>
#include <map>

/**
 * @brief initializes new sqlite file. if it alreadt exists it does nothing
 * 
 * @param filepath the path of the file
 */
void initialize_database(const std::string& filepath);

/**
 * @brief Get the past data from the database
 * 
 * @param filepath darabase filepath
 * @return map that maps from pair of product and language, to vector of results in past
 */
std::map<std::pair<std::string, std::string>, std::vector<std::string>> get_past_data(const std::string& filepath);