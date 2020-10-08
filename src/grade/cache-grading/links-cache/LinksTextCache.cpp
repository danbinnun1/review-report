#include "LinksTextCache.hpp"
#include "split.hpp"
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>

void grading::LinksTextCache::insertLink(const std::string &link) {
    FILE *file = fopen(m_filePath.c_str(), "a");
    if (file == NULL) {
        throw std::runtime_error("could not open file.");
    }
    fprintf(file, "%s\n", link.c_str());
    fclose(file);
}

inline bool fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

bool grading::LinksTextCache::linkInCache(const std::string &link) const {
    if (!fileExists(m_filePath)) return false;
    std::ifstream t;
    int length;
    t.open(m_filePath);
    t.seekg(0, std::ios::end);
    length = t.tellg();
    t.seekg(0, std::ios::beg);
    auto buffer = new char[length];
    t.read(buffer, length);
    t.close();
    auto cacheLinks = splitByDelimiter(buffer, '\n');
    return std::find(cacheLinks.begin(), cacheLinks.end(), link) !=
           cacheLinks.end();
}

grading::LinksTextCache::LinksTextCache(std::string filePath) : m_filePath(filePath) {}
