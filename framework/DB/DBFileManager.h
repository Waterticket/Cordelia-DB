//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_DBFILEMANAGER_H
#define CORDELIA_DB_DBFILEMANAGER_H
#include "../FileHandler.h";

class DBFileManager {
public:
    std::string open(std::string filename)
    {
        this->filename = filename;
        FileValue = fh.read(filename);

        return FileValue;
    }

    std::string getFileValue()
    {
        return this->FileValue;
    }

    std::string getFileName()
    {
        return filename;
    }

private:
    std::string filename;
    std::string FileValue;
    FileHandler fh;
};

#endif //CORDELIA_DB_DBFILEMANAGER_H
