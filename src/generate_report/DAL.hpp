#pragma once
#include <string>

/**
 * @brief initializes new sqlite file. if it alreadt exists it does nothing
 * 
 * @param filepath the path of the file
 */
void initialize_database(const std::string& filepath);

