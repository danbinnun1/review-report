#pragma once
#include <string>
namespace grading
{
  class LinksCache
  {

  public:
    virtual void insertLink(const std::string &link) = 0;
    virtual bool linkInCache(const std::string &link) const = 0;
    virtual ~LinksCache() = default;
  };
} // namespace grading