#include "LinuxURLOpener.hpp"

void grading::LinuxURLOpener::openLink(const std::string &link) const{
    const std::string systemCall="xdg-open ";
    system((systemCall + link).c_str());
}