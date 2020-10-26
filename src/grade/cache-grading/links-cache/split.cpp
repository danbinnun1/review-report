#include "split.hpp"
#include <sstream>
#include <iostream>

std::vector<std::string> splitByDelimiter(const char *str,
                                          const char delimiter)
{
    std::vector<std::string> parts = {};
    std::stringstream ss(str);
    std::string to;
    if (str != NULL)
    {
        while (std::getline(ss, to, delimiter))
        {
            parts.push_back(to);
        }
    }
    return parts;
}

std::vector<std::string> splitRows(const std::string &str)
{
    std::istringstream stream;
    stream.str(str);
    std::vector<std::string> result = {};
    for (std::string line; std::getline(stream, line);)
    {

        result.push_back(line.substr(0,line.size()-1));
    }
    return result;
}