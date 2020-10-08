#pragma once
#include <vector>
#include <string>
namespace google_search {
class Searcher
{

public:
    //search links
    virtual std::vector<std::string> search(const std::string& product) const = 0;
    virtual ~Searcher() = default;
};
}