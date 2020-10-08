#include "LinuxURLOpener.hpp"

void grading::LinuxURLOpener::openLink(const std::string &link) const{
    const std::string systemCall="xdg-open "+link;
    system(systemCall.c_str());
}