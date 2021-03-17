//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_RESULTSET_H
#define CORDELIA_DB_RESULTSET_H

class ResultSet {
public:
    std::vector< std::string > column_name;
    std::vector< std::string > column_type; //int, string, etc..
    std::vector< std::string > column_opt; // PK(primary_key), AI(auto_increment), etc..

    std::vector< std::vector < std::string > > table_tuples; // data
};

#endif //CORDELIA_DB_RESULTSET_H
