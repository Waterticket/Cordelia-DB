#include <iostream>

#include "framework/DBHandler.h";

int main() {
    DBHandler dh;
    dh.executeQuery("SELECT a,b,c FROM asdf lol");
    return 0;
}
