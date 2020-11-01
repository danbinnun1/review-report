#include "DBRanking.hpp"
#include "DBPath.hpp"
#include "unqlite.h"
#include "DBHelper.hpp"
#include <stdexcept>
#include <iostream>
#include "MapTable.hpp"

#define RATING_SCHEMA "rating"
#define RATING_DATA_VAR_NAME "data"
#define DATA_KEY_NAME "data"


static int append_record_to_vector(unqlite_value *pKey, unqlite_value *pData, void *pUserData);

std::unique_ptr<history_reports_data> get_past_data()
{
    std::vector<MapTable<std::string,std::string,std::string>> tables;
    unqlite *pDb;
    unqlite_vm *pVm;

    if (unqlite_open(&pDb, DATABASE_PATH, UNQLITE_OPEN_CREATE) != UNQLITE_OK)
    {
        fatal(0, "out of memory");
    }
    const std::string jx9_script = "$" + std::string(RATING_DATA_VAR_NAME) + " = db_fetch_all('" + std::string(RATING_SCHEMA) + "');";
    if (unqlite_compile(pDb, jx9_script.c_str(), jx9_script.size(), &pVm) != UNQLITE_OK)
    {
        handle_jx9_compilation_error(pDb);
    }
    unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_OUTPUT, vmOutputConsumer, 0);
    unqlite_vm_exec(pVm);
    unqlite_value *data = unqlite_vm_extract_variable(pVm, RATING_DATA_VAR_NAME);
    unqlite_array_walk(data, append_record_to_vector, static_cast<void *>(&tables));
    unqlite_vm_release_value(pVm, data);
    unqlite_vm_release(pVm);
    unqlite_close(pDb);
    std::unique_ptr<history_reports_data> result=std::make_unique<MapTable<std::string,std::string,std::vector<std::string>>>();
    for (const auto& record:tables){
        for (const auto& row:record.get_rows()){
            for (const auto& col:record.get_columns()){
                std::string string_value;

                //check if the value exists in the table, if it doesn't, it will throw exception
                try{
                    string_value=record.get_value(row,col);
                }
                catch(std::exception& e){
                    string_value="";
                }

                try{
                    result->get_value(row,col);
                }
                catch (std::exception& e){
                    result->set_value(row,col,{});
                }
                auto vec=result->get_value(row,col);

                vec.push_back(record.get_value(row,col));
                result->set_value(row,col,vec);
 
            }
        }
    }
    return result;
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
    unqlite_value *result_data;
    result_data = unqlite_vm_new_array(pVm);

    const auto products=data.get_rows();
    const auto languages=data.get_columns();

    for (const std::string &product:products){
        unqlite_value* product_data=unqlite_vm_new_array(pVm);
        for (const std::string& language:languages){
            std::string string_value;

            //check if the value exists in the table, if it doesn't, it will throw exception
            try{
                string_value=data.get_value(product,language);
            }
            catch(std::exception& e){
                string_value="";
            }
            
            unqlite_value* value;
            value = unqlite_vm_new_scalar(pVm);
            unqlite_value_string(value, string_value.c_str(),-1);
            unqlite_array_add_strkey_elem(product_data,language.c_str(),value);
            unqlite_vm_release_value(pVm, value);
        }
        unqlite_array_add_strkey_elem(result_data,product.c_str(),product_data);
        unqlite_vm_release_value(pVm, product_data);
    }
    unqlite_value* result=unqlite_vm_new_array(pVm);
    unqlite_array_add_strkey_elem(result,DATA_KEY_NAME,result_data);
    unqlite_vm_release_value(pVm,result_data);
    return result;
}

typedef struct {
    std::string product_name;
    MapTable<std::string,std::string,std::string>* table;
} language_data;


static int append_language_to_map(unqlite_value *pKey, unqlite_value *pData, void *pUserData){

    language_data* lang_data=static_cast<language_data*>(pUserData);
    
    lang_data->table->set_value(lang_data->product_name,std::string(unqlite_value_to_string(pKey,NULL)),std::string(unqlite_value_to_string(pData,NULL)));
    return UNQLITE_OK;
}

static int append_product_to_map(unqlite_value *pKey, unqlite_value *pData, void *pUserData){
    language_data lang_data;
    lang_data.product_name=std::string(unqlite_value_to_string(pKey,NULL));

    lang_data.table=static_cast<MapTable<std::string,std::string,std::string>*>(pUserData);

    unqlite_array_walk(pData, append_language_to_map, static_cast<void *>(&lang_data));

    return UNQLITE_OK;
}

static int append_record_to_vector(unqlite_value *pKey, unqlite_value *pData, void *pUserData){
    unqlite_value *data = unqlite_array_fetch(pData, DATA_KEY_NAME, sizeof(DATA_KEY_NAME) - 1);
    MapTable<std::string,std::string,std::string> table;
    unqlite_array_walk(data, append_product_to_map, static_cast<void *>(&table));

    std::vector<MapTable<std::string,std::string,std::string>>* tables=static_cast<std::vector<MapTable<std::string,std::string,std::string>>*>(pUserData);
    tables->push_back(table);

    unqlite_value_release(data);

    return UNQLITE_OK;
}