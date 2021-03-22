#ifndef CORDELIA_DB_DBHANDLER_H
#define CORDELIA_DB_DBHANDLER_H

#include <map>
#include "DB/DBFileManager.h";
#include "DB/ResultSet.h";
#include "StringHandler.h";
#include "ExceptionHandler.h";

class DBHandler{
public:
    std::string sql_string;

    ResultSet executeQuery(std::string sql_string)
    {
        this->sql_string = sql_string;
        this->ArgSetter(sql_string);
        this->_execute();

        return rs;
    }

private:
    DBFileManager DBFile;
    StringHandler StrHandler;
    std::vector<std::string> sql_strs;
    ResultSet rs;

    std::string execute_type; // SELECT, INSERT, UPDATE, DELETE
    std::string execute_table;
    std::vector < std::tuple < std::string, std::string, std::string > > search_condition; // Key, Value, Condition

    DBTable dt;

    bool ArgSetter(std::string sql_string)
    {
        sql_strs = StrHandler.tokenize_getline(sql_string, ' ');
        this->setType(sql_strs[0]);

        if(execute_type == "SELECT")
        {
            int pos_from = -1;
            int pos_where = -1;
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
                    select_columns.push_back(columns[j]); // 컬럼 집어넣기
                }
            }

            if(pos_where >= 0)
            {
                for (int i = pos_where+1; i < sql_strs.size(); i++)
                {
                    if(StrHandler.toUpper(trim(sql_strs[i])) == ("AND")) continue; // AND에 경우 패스 (다음 구문 분석)

                    std::vector<std::string> key_val = StrHandler.tokenize_getline(sql_strs[i], '=');
                    if(key_val.size() < 2) Exceptions(E_ERROR, "delimiter parse failed in `WHERE` syntax");

                    search_condition.push_back(std::make_tuple(key_val[0], key_val[1], "="));
                }
            }
        }
    }

    void setTable(std::string table)
    {
        ConsoleLog("Table:"+table);
        this->execute_table = table;
        dt = DBFile.openTable(table);
    }

    void setType(std::string type)
    {
        std::transform(type.begin(), type.end(), type.begin(), toupper);
        this->execute_type = type;
    }

    void _execute()
    {
        // 기존 DB 데이터 복사
        rs.column_name = dt.column_name;
        rs.column_type = dt.column_type;
        rs.column_opt = dt.column_opt;

        if(execute_type == "SELECT")
        {
            //WHERE 계산
            std::vector< std::vector < std::string > > rtn_table_object = dt.table_tuples;

            for(int i = 0; i < search_condition.size(); i++)
            {
                std::string key = std::get<0>(search_condition[i]);
                std::string value = std::get<1>(search_condition[i]);
                std::string cond = std::get<2>(search_condition[i]);

                int attr_pos = -1;

                for(int i = 0; i < dt.column_type.size(); i++)
                {
                    if(dt.column_name[i] == key)
                    {
                        attr_pos = i; // 속성 (열)의 위치
                        break;
                    }
                }

                if(attr_pos < 0) Exceptions(E_ERROR, "Unable to find column name ["+key+"]");

                std::vector < std::vector < std::string > > temp_table_object; // 임시 검색 데이터 저장용 벡터

                for(int i = 0; i < rtn_table_object.size(); i++)
                {
                    std::vector < std::string > row = rtn_table_object[i];
                    if(trim(row[attr_pos]) == value) //row[attr_pos] cond value
                        // @todo cond 종류 다양화
                    {
                        temp_table_object.push_back(row);
                    }
                }

                rtn_table_object = temp_table_object; // 검색 데이터 저장, (condition이 더 남아있다면 이걸 이용해서 계속 진행)
            }

            rs.table_tuples = rtn_table_object; // 최종 데이터 제공
            return; // SELECT 끝
        }
    }
};


#endif //CORDELIA_DB_DBHANDLER_H
