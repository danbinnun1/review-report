#pragma once
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> splitByDelimiter(const char* str,
                                          const char delimiter);

std::vector<std::string> splitRows(const std::string& str);