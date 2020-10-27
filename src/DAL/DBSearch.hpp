#pragma once
#include <map>
#include <vector>
#include <string>

/**
 * @brief checks if the databse exists
 * 
 * @return true if the database exists
 * @return false else
 */
bool database_exists();

/**
 * @brief initialize the database
 * 
 * @param searching_data map that maps from product to list of languages
 */
void create_database(const std::map<std::string, std::vector<std::string>>& searching_data);

/**
 * @brief return the search data of the database
 * 
 * @return std::map<std::string, std::vector<std::string>> map that maps from product to list of languages
 */
std::map<std::string, std::vector<std::string>> get_searching_data();