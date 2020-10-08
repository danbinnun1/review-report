#pragma once
#include "LinksCache.hpp"
#include <string>
namespace grading {
class LinksTextCache : public LinksCache {
private:
  std::string m_filePath;

public:
  LinksTextCache(std::string filePath);

  void insertLink(const std::string &link) override;
  bool linkInCache(const std::string &link) const override;

};
} // namespace grading