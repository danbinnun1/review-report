#pragma once
#include "URLOpener.hpp"
namespace grading
{
    class LinuxURLOpener : public URLOpener
    {
    public:
        void openLink(const std::string& link) const override;
    };
} // namespace grading