#include <iostream>

#include "framework/DBHandler.h";

int main() {
    DBHandler dh;
    ResultSet rs = dh.executeQuery("SELECT a,b,c FROM dbtest WHERE index=2");

    for(int i = 0; i < rs.table_tuples.size(); i++)
    {
        for(int j = 0; j < rs.table_tuples[i].size(); j++)
        {
            std::cout << rs.table_tuples[i][j] << " ";
        }

        std::cout << std::endl;
    }
    return 0;
}
