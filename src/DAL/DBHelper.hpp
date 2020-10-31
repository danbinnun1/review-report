#pragma once
#include "unqlite.h"
#include <string>
#include <vector>
#include <map>

int vmOutputConsumer(const void *pOutput, unsigned int nOutLen, void *pUserData);

void fatal(unqlite *pDb, const char *zMsg);

void handle_jx9_compilation_error(unqlite* pDb);