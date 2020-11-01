#include "DBRanking.hpp"
#include "DBPath.hpp"
#include "unqlite.h"
#include "DBHelper.hpp"
#include <stdexcept>
#include <iostream>

#define RATING_SCHEMA "rating"
#define RATING_DATA_VAR_NAME "data"

std::unique_ptr<history_reports_data> get_past_data()
{
    return nullptr;
}

static unqlite_value *get_unqlite_table(const report_data &data, unqlite_vm* pVm);

void insert_new_data(const report_data &data)
{
    unqlite* pDb;
    if (unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE) != UNQLITE_OK)
    {
        fatal(0, "can't open database, out of memory");
    }
    unqlite_vm* pVm;

    const std::string jx9_script =
        std::string("$zCol = '") + RATING_SCHEMA + "';"
        "if (!db_exists($zCol)) {"
        "   $rc = db_create($zCol);"
        "   if ( !$rc ){"
        "       print db_errlog();"
        "       return;"
        "   }"
        "}"
        "db_store('"+RATING_SCHEMA"', $"+RATING_DATA_VAR_NAME+");";


    if (unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm) != UNQLITE_OK)
    {
        handle_jx9_compilation_error(pDb);
    }
    unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_OUTPUT, vmOutputConsumer, 0);
    unqlite_value* table=get_unqlite_table(data, pVm);
    if (unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_CREATE_VAR, RATING_DATA_VAR_NAME, table) != UNQLITE_OK)
    {
        fatal(0, "error while installing data");
    }
    unqlite_vm_exec(pVm);
    unqlite_vm_release_value(pVm, table);
    unqlite_vm_release(pVm);
    unqlite_close(pDb);

}

static unqlite_value *get_unqlite_table(const report_data &data, unqlite_vm* pVm)
{
    unqlite_value *result;
    result = unqlite_vm_new_array(pVm);

    const auto products=data.get_rows();
    const auto languages=data.get_columns();

    for (const std::string &product:products){
        unqlite_value* product_data=unqlite_vm_new_array(pVm);
        for (const std::string& language:languages){
            const std::string string_value=data.get_value(product,language);
            unqlite_value* value;
            value = unqlite_vm_new_scalar(pVm);
            unqlite_value_string(value, string_value.c_str(),-1);
            unqlite_array_add_strkey_elem(product_data,language.c_str(),value);
            unqlite_vm_release_value(pVm, value);
        }
        unqlite_array_add_strkey_elem(result,product.c_str(),product_data);
        unqlite_vm_release_value(pVm, product_data);
    }
    return result;
}
