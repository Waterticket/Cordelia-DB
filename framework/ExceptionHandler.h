//
// Created by Administrator on 2021-03-17.
//

#ifndef CORDELIA_DB_EXCEPTIONHANDLER_H
#define CORDELIA_DB_EXCEPTIONHANDLER_H

#include "Library/color.h";
#include "StringHandler.h";

#define Exceptions(x,y) ExceptionHandler(x,y,__FUNCTION__,__LINE__,__FILE__)
#define ConsoleLog(x) ExceptionHandler(E_NOTICE,x,__FUNCTION__,__LINE__,__FILE__)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define E_EXCEPTION 0
#define E_ERROR 1
#define E_WARNING 2
#define E_NOTICE 3

class ExceptionHandler {
public:
    ExceptionHandler(int code, const std::string& msg, std::string callfunc = __FUNCTION__, int callline = __LINE__, std::string filename = "")
    {
        switch(code)
        {
            case E_EXCEPTION:
                std::cout << dye::light_red("Exception: ") << dye::yellow(msg) << " in " << filename << " " << dye::yellow(callfunc) << dye::yellow("()") << " on line " << callline << std::endl;
                break;

            case E_ERROR:
                std::cout << dye::light_red("Error: ") << dye::light_red(msg) << " in " << filename << " " << dye::yellow(callfunc) << dye::yellow("()") << " on line " << callline << std::endl;
                break;

            case E_WARNING:
                std::cout << dye::yellow("Warning: ") << dye::yellow(msg) << " in " << filename << " " << dye::yellow(callfunc) << dye::yellow("()") << " on line " << callline << std::endl;
                break;

            case E_NOTICE:
                std::cout << dye::green("Notice: ") << msg << " in " << filename << " " << callfunc << "()" << " on line " << callline << std::endl;
                break;

            default:
                break;
        }
        if(code < E_WARNING)
            throw std::invalid_argument(msg);
    }
};

#endif //CORDELIA_DB_EXCEPTIONHANDLER_H
