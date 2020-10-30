#include "DBSearch.hpp"
#include "DBPath.hpp"
#include "unqlite.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "DBHelper.hpp"

#define SEARCH_DATA_SCHEMA "search"
#define SEARCH_DATA_VAR_NAME "searchData"


static unqlite_value *get_unqlite_array(const std::map<std::string, std::vector<std::string>> &searching_data, unqlite_vm *pVm);


inline bool file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

bool database_exists()
{
    return file_exists(DATABASE_PATH);
}

void create_database(const std::map<std::string, std::vector<std::string>> &searching_data)
{
    unqlite *pDb;
    unqlite_vm *pVm;
    int rc;
    rc = unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE);

    if (rc != UNQLITE_OK)
    {
        Fatal(0, "can't open database, out of memory");
    }
    //unqlite_vm_
    const std::string jx9_script =
        "$zCol = '" + std::string(SEARCH_DATA_SCHEMA) + "';"
        "if (db_exists($zCol)) {"
        "   print \"search collection already exists\";"
        "}"
        "$rc = db_create($zCol);"
        "if ( !$rc ){"
        "   print db_errlog();"
        "   return;"
        "}"
        "db_store($zCol, $" +
        SEARCH_DATA_VAR_NAME + ");"
        "if (!$rc) {"
        "   print db_errorlog();"
        "    return;"
        "}";
    rc = unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm);
    if (rc != UNQLITE_OK)
    {
        const char *zBuf;
        int iLen;
        unqlite_config(pDb, UNQLITE_CONFIG_JX9_ERR_LOG, &zBuf, &iLen);
        if (iLen > 0)
        {
            puts(zBuf);
        }
        Fatal(0, "Jx9 compile error");
    }
    unqlite_value *insertion_data = get_unqlite_array(searching_data, pVm);
    rc = unqlite_vm_config(
        pVm,
        UNQLITE_VM_CONFIG_CREATE_VAR,
        SEARCH_DATA_VAR_NAME,
        insertion_data);
    if (rc != UNQLITE_OK)
    {
        Fatal(0, "Error while installing $my_app");
    }
    unqlite_vm_exec(pVm);
    unqlite_vm_release(pVm);
    unqlite_close(pDb);
}

std::map<std::string, std::vector<std::string>> get_searching_data()
{
    std::map<std::string, std::vector<std::string>> result;
    unqlite* pDb;
    if(unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE)!=UNQLITE_OK){
        Fatal(0, "out of memory");
    }
    const std::string jx9_script="$"+std::string(SEARCH_DATA_VAR_NAME)+"=db_fetch_all('"+std::string(SEARCH_DATA_SCHEMA)+"');";
    unqlite_vm* pVm;
    if (unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm)!=UNQLITE_OK){
        const char *zBuf;
        int iLen;
        unqlite_config(pDb, UNQLITE_CONFIG_JX9_ERR_LOG, &zBuf, &iLen);
        if (iLen > 0)
        {
            puts(zBuf);
        }
        Fatal(0, "Jx9 compile error");
    }
    unqlite_vm_exec(pVm);
    unqlite_value* data=unqlite_vm_extract_variable(pVm, SEARCH_DATA_VAR_NAME);
    unqlite_array_walk(data,append_vector_to_map,static_cast<void*>(&result));
    unqlite_vm_release_value(pVm, data);
    unqlite_vm_release(pVm);
    unqlite_close(pDb);
    return result;

}
static unqlite_value *get_unqlite_array(const std::map<std::string, std::vector<std::string>> &searching_data, unqlite_vm *pVm)
{
    unqlite_value *map;
    map = unqlite_vm_new_array(pVm);

    for (const auto &element : searching_data)
    {
        unqlite_value *value;
        unqlite_value *array_key;
        array_key = unqlite_vm_new_scalar(pVm);
        const auto key = element.first;
        const auto strings = element.second;
        unqlite_value_string(array_key, key.c_str(), -1);
        value = unqlite_vm_new_array(pVm);

        for (const std::string &str : strings)
        {
            unqlite_value *temp_array_value;
            temp_array_value = unqlite_vm_new_scalar(pVm);
            unqlite_value_string(temp_array_value, str.c_str(), -1);
            unqlite_array_add_elem(value, NULL, temp_array_value);
            unqlite_vm_release_value(pVm, temp_array_value);
        }

        unqlite_array_add_elem(map, array_key, value);
        unqlite_vm_release_value(pVm, value);
        unqlite_vm_release_value(pVm, array_key);
    }
    return map;
}

