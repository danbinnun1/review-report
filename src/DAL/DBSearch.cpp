#include "DBSearch.hpp"
#include "DBPath.hpp"
#include "unqlite.h"
#include "DBHelper.hpp"

#include <sys/stat.h>

#define SEARCH_DATA_SCHEMA "search"
#define SEARCH_DATA_VAR_NAME "searchData"

#define RECORD_KEY "product"
#define RECORD_VALUE "languages"

static int append_string_to_vector(unqlite_value *pKey, unqlite_value *pData, void *pUserData);

static unqlite_value *get_unqlite_array(const std::map<std::string, std::vector<std::string>> &searching_data, unqlite_vm *pVm);

static int append_record_to_map(unqlite_value *pKey, unqlite_value *pData, void *pUserData);

inline bool file_exists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool database_exists()
{
    return file_exists(DATABASE_PATH);
}

void create_database(const std::map<std::string, std::vector<std::string>> &searching_data)
{
    unqlite *pDb;
    unqlite_vm *pVm;

    if (unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE) != UNQLITE_OK)
    {
        fatal(0, "can't open database, out of memory");
    }

    const std::string jx9_script =
        "$zCol = '" + std::string(SEARCH_DATA_SCHEMA) + "';"
                                                        "if (db_exists($zCol)) {"
                                                        "   print \"search collection already exists\";"
                                                        "   return;"
                                                        "}"
                                                        "$rc = db_create($zCol);"
                                                        "if ( !$rc ){"
                                                        "   print db_errlog();"
                                                        "   return;"
                                                        "}"
                                                        "$insert=function($value, $key){"
                                                        "   $data = {'" +
        RECORD_KEY + "':$key, '" + RECORD_VALUE + "' : $value};"
                                                  "   $rc = db_store('" +
        SEARCH_DATA_SCHEMA + "', $data);"
                             "   if (!$rc){"
                             "       print db_errlog();"
                             "   }"
                             "   print $data;"
                             "};"
                             "array_walk($" +
        SEARCH_DATA_VAR_NAME + ", $insert);";

    if (unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm) != UNQLITE_OK)
    {
        handle_jx9_compilation_error(pDb);
    }
    unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_OUTPUT, vmOutputConsumer, 0);
    unqlite_value *insertion_data = get_unqlite_array(searching_data, pVm);
    if (unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_CREATE_VAR, SEARCH_DATA_VAR_NAME, insertion_data) != UNQLITE_OK)
    {
        fatal(0, "Error while installing data");
    }
    unqlite_vm_exec(pVm);
    unqlite_vm_release(pVm);
    unqlite_close(pDb);
}

std::map<std::string, std::vector<std::string>> get_searching_data()
{
    std::map<std::string, std::vector<std::string>> result;
    unqlite *pDb;
    unqlite_vm *pVm;

    if (unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE) != UNQLITE_OK)
    {
        fatal(0, "out of memory");
    }
    const std::string jx9_script = "$" + std::string(SEARCH_DATA_VAR_NAME) + "=db_fetch_all('" + std::string(SEARCH_DATA_SCHEMA) + "');";
    if (unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm) != UNQLITE_OK)
    {
        handle_jx9_compilation_error(pDb);
    }
    unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_OUTPUT, vmOutputConsumer, 0);
    unqlite_vm_exec(pVm);
    unqlite_value *data = unqlite_vm_extract_variable(pVm, SEARCH_DATA_VAR_NAME);
    unqlite_array_walk(data, append_record_to_map, static_cast<void *>(&result));
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

static int append_record_to_map(unqlite_value *pKey, unqlite_value *pData, void *pUserData)
{
    unqlite_value *product = unqlite_array_fetch(pData, RECORD_KEY, sizeof(RECORD_KEY) - 1);
    std::string product_name = std::string(unqlite_value_to_string(product, NULL));
    unqlite_value *languages = unqlite_array_fetch(pData, RECORD_VALUE, sizeof(RECORD_VALUE) - 1);
    std::vector<std::string> languages_vec;
    unqlite_array_walk(languages, append_string_to_vector, static_cast<void *>(&languages_vec));
    std::map<std::string, std::vector<std::string>> *map = static_cast<std::map<std::string, std::vector<std::string>> *>(pUserData);

    map->insert(std::make_pair(product_name, languages_vec));
    return UNQLITE_OK;
}

static int append_string_to_vector(unqlite_value *pKey, unqlite_value *pData, void *pUserData)
{
    std::vector<std::string> *vec = static_cast<std::vector<std::string> *>(pUserData);
    const char *zData;
    zData = unqlite_value_to_string(pData, NULL);
    vec->push_back(std::string(zData));
    return UNQLITE_OK;
}