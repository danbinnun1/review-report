#pragma once
#include "LinksCache.hpp"
#include <string>
namespace grading {
class LinksTextCache : public LinksCache {
private:
  std::string filePath;

public:
  void insertLink(const std::string &link) override;
  bool linkInCache(const std::string &link) const override;
};
} // namespace grading