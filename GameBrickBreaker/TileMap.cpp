#include "TileMap.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool TileMap::LoadTile(int number)
{
    ifstream in_file;
    if (number%2)
    {
    string map="map/map"+std::to_string(number)+".txt";
    in_file.open(map);
    } else in_file.open("map/empty.txt");
    if(in_file.fail())
    {
        cout << "file khong ton tai" << endl;
        return false;
    }

    for(int i = 0; i < number_brick_y; i++)
    {
        for(int j = 0; j < number_brick_x; j++)
        {
            in_file >> tile[i][j];
        }
    }
    in_file.close();

    return true;
}
