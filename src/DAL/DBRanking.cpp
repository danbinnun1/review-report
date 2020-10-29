#include "DBRanking.hpp"
#include "DBPath.hpp"
#include "unqlite.h"
#include <stdexcept>
#include <iostream>

std::unique_ptr<history_reports_data> get_past_data()
{
    return nullptr;
}

void insert_new_data(const report_data &data)
{
}