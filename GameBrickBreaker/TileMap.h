#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

const int number_brick_x = 10;
const int number_brick_y = 4;

class TileMap
{
public:
    int tile[number_brick_y][number_brick_x];
    bool LoadTile(int number);

};

#endif // TILEMAP_H_INCLUDED
