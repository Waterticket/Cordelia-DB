//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_STRINGHANDLER_H
#define CORDELIA_DB_STRINGHANDLER_H

#define bold(x) "\e[1m" << x << "\e[0m"
#define italic(x) "\e[3m" << x << "\e[0m"
#define underline(x) "\e[4m" << x << "\e[24m"
#define inverse(x) "\e[7m" << x << "\e[27m"

#define black(x) "\033[30m" << x <<"\033[0m"
#define red(x) "\033[31m" << x <<"\033[0m"
#define green(x) "\033[32m" << x <<"\033[0m"
#define yellow(x) "\033[33m" << x <<"\033[0m"
#define blue(x) "\033[34m" << x <<"\033[0m"
#define magenta(x) "\033[35m" << x <<"\033[0m"
#define cyan(x) "\033[36m" << x <<"\033[0m"
#define white(x) "\033[37m" << x <<"\033[0m"

#include <vector>
#include <sstream>
#include <algorithm>

class StringHandler{
public:
    std::vector<std::string> tokenize_getline(const std::string& data, const char delimiter = ' ');
    std::vector<std::string> tokenize_getline_str(const std::string& data, const std::string delimiter = "");
    std::string erase_str(std::string s, std::string delimiter = "");
    std::string toLower(std::string s);
};

std::vector<std::string> StringHandler::tokenize_getline(const std::string& data, const char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(data);

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::vector<std::string> StringHandler::tokenize_getline_str(const std::string& data, const std::string delimiter) {
    std::vector<std::string> result;
    std::string s = data;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);

    return result;
}

std::string StringHandler::erase_str(std::string s, std::string delimiter)
{
    int ds = delimiter.size();
    while(s.find(delimiter) != std::string::npos)
    {
        s.erase(s.find(delimiter), ds);
    }

    return s;
}

std::string StringHandler::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

//앞에 있는 개행 문자 제거
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

//뒤에 있는 개행 문자 제거
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

//양쪽 끝의 개행 문자 제거
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

#endif //CORDELIA_DB_STRINGHANDLER_H
