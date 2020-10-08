#include "split.hpp"

std::vector<std::string> splitByDelimiter(const char *str,
                                          const char delimiter) {
    std::vector<std::string> parts = {};
    std::stringstream ss(str);
    std::string to;
    if (str != NULL) {
        while (std::getline(ss, to, delimiter)) {
            parts.push_back(to);
        }
    }
    return parts;
}