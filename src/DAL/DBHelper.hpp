#pragma once
#include "unqlite.h"
#include <string>
#include <vector>
#include <map>

int VmOutputConsumer(const void *pOutput, unsigned int nOutLen, void *pUserData);

void Fatal(unqlite *pDb, const char *zMsg);
