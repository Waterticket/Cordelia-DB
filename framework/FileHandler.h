//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_FILEHANDLER_H
#define CORDELIA_DB_FILEHANDLER_H

#include <fstream>
#include <string>

class FileHandler{
public:
    std::string read(std::string fname);
    bool write(std::string fname, std::string value);
    bool write_relay(std::string fname, std::string value);

    FileHandler()
    {

    }
};

// 파일 읽기
std::string FileHandler::read(std::string fname)
{
    std::ifstream in(fname);
    std::string s;

    if (in.is_open()) {
        in.seekg(0, std::ios::end);
        int size = in.tellg();
        s.resize(size);
        in.seekg(0, std::ios::beg);
        in.read(&s[0], size);
    } else {
        throw std::invalid_argument("INVAILD_FILENAME");
    }

    in.close();
    return s;
}

// 파일 쓰기
bool FileHandler::write(std::string fname, std::string value)
{
    std::ofstream out(fname);

    if (out.is_open()) {
        out << value;
    } else {
        throw std::invalid_argument("INVAILD_FILENAME");
    }

    return true;
}

// 파일 이어서 쓰기
bool FileHandler::write_relay(std::string fname, std::string value)
{
    std::ofstream out(fname, std::ios::app);

    if (out.is_open()) {
        out << value;
    } else {
        throw std::invalid_argument("INVAILD_FILENAME");
    }

    return true;
}

#endif //CORDELIA_DB_FILEHANDLER_H
