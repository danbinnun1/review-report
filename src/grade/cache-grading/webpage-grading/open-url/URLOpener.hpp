#pragma once
#include <string>
namespace grading
{
    class URLOpener
    {

    public:
        virtual void openLink(const std::string &link) const = 0;
        virtual ~URLOpener() = default;
    };
} // namespace grading