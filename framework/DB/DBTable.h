//
// Created by Administrator on 2021-03-16.
//

#ifndef CORDELIA_DB_DBTABLE_H
#define CORDELIA_DB_DBTABLE_H

#include <vector>

#include "../StringHandler.h";

class DBTable {
public:
    std::vector< std::string > column_name;
    std::vector< std::string > column_type; //int, string, etc..
    std::vector< std::string > column_opt; // PK(primary_key), AI(auto_increment), etc..

    std::vector< std::vector < std::string > > table_tuples; // data

    DBTable()
    {
        // empty class
    }

    DBTable(std::string data)
    {
        StringHandler sh;
        std::vector< std::string > lines = sh.tokenize_getline(data, '\n');

        column_name = sh.tokenize_getline(lines[0], ',');
        column_type = sh.tokenize_getline(lines[1], ',');
        column_opt = sh.tokenize_getline(lines[2], ',');

        for (int i = 3; i < lines.size(); i++)
        {
            std::vector< std::string > data = sh.tokenize_getline(lines[i], ',');

            table_tuples.push_back(data);
        }
    }
};

#endif //CORDELIA_DB_DBTABLE_H
