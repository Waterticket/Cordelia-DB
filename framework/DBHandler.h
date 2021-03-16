#ifndef CORDELIA_DB_DBHANDLER_H
#define CORDELIA_DB_DBHANDLER_H

#include <map>
#include "DB/DBFileManager.h";
#include "DB/ResultSet.h";
#include "StringHandler.h";

class DBHandler{
public:
    std::string sql_string;

    ResultSet executeQuery(std::string sql_string)
    {
        this->sql_string = sql_string;
        this->ArgSetter(sql_string);

        return rs;
    }

private:
    DBFileManager DBFile;
    StringHandler StrHandler;
    std::vector<std::string> sql_strs;
    ResultSet rs;

    std::string execute_type; // SELECT, INSERT, UPDATE, DELETE
    std::string execute_table;

    bool ArgSetter(std::string sql_string)
    {
        sql_strs = StrHandler.tokenize_getline(sql_string, ' ');
        this->setType(sql_strs[0]);

        if(execute_type == "SELECT")
        {
            int pos_from = 0;
            int pos_where = 0;
            std::vector< std::string > select_columns;

            for (int i = 0; i < sql_strs.size(); i++)
            {
                // FROM 찾기
                if(StrHandler.toLower(sql_strs[i]) == StrHandler.toLower("FROM"))
                {
                    pos_from = i;
                    this->setTable(sql_strs[i+1]);
                }

                // WHERE 찾기
               if(StrHandler.toLower(sql_strs[i]) == StrHandler.toLower("WHERE"))
                {
                    pos_where = i;
                }
            }

            // 컬럼 등록
            for (int i = 1; i < pos_from; i++)
            {
                std::string column =  sql_strs[i];
                std::vector<std::string> columns = StrHandler.tokenize_getline(column, ',');
                for(int j = 0; j < columns.size(); j++)
                {
                    select_columns.push_back(columns[j]);
                    std::cout << "column:" << columns[j] << std::endl;
                }
            }
        }
    }

    bool setTable(std::string table)
    {
        std::cout << "Table:" << table << std::endl;
        this->execute_table = table;
        //DBFile.open(table + ".");
    }

    bool setType(std::string type)
    {
        std::transform(type.begin(), type.end(), type.begin(), toupper);
        this->execute_type = type;
    }
};


#endif //CORDELIA_DB_DBHANDLER_H
