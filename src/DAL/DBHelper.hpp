#pragma once
#include "unqlite.h"
#include <string>
#include <vector>
#include <map>

int append_string_to_vector(unqlite_value* pKey, unqlite_value* pData, void* pUserData);

int append_vector_to_map(unqlite_value* pKey, unqlite_value* pData, void* pUserData);

int VmOutputConsumer(const void *pOutput, unsigned int nOutLen, void *pUserData);

void Fatal(unqlite *pDb, const char *zMsg);
