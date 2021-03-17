//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_DBFILEMANAGER_H
#define CORDELIA_DB_DBFILEMANAGER_H
#include "../FileHandler.h";
#include "DBTable.h";

class DBFileManager {
private:
    std::string filename;
    std::string FileValue;
    FileHandler fh;

public:
    std::string open(std::string filename)
    {
        FileValue = fh.read(filename);

        return FileValue;
    }

    DBTable openTable(std::string filename)
    {
        this->filename = filename;
        std::string f_value = this->open("../files/database/"+filename+".csv"); // FileHandler.h 기준 폴더 경로
        return DBTable(f_value); //Table Class 리턴
    }

    std::string getFileValue()
    {
        return this->FileValue;
    }

    std::string getFileName()
    {
        return filename;
    }
};

#endif //CORDELIA_DB_DBFILEMANAGER_H
