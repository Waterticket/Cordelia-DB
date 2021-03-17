cmake_minimum_required(VERSION 3.17)
project(cordelia_db)

set(CMAKE_CXX_STANDARD 14)

add_executable(cordelia_db main.cpp framework/DBHandler.h framework/DB/DBFileManager.h framework/FileHandler.h framework/DB/ResultSet.h framework/StringHandler.h framework/DB/DBTable.h framework/ExceptionHandler.h framework/DB/TableBase.h)