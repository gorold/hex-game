#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

#include "HexGraph.hpp"

using namespace std;

#ifndef HEXBOARD_H
#define HEXBOARD_H

class HexBoard {
  public:
    HexBoard(int size);
    bool place_tile(int i, int j, HexTile tile);
    bool remove_tile(int i, int j);
    bool replace_tile(int i, int j);
    bool is_connected(HexTile player);
    friend ostream& operator<<(ostream& out, HexBoard& board);
    vector<pair<HexTile, vector<int>>> get_edge_list();
    
  private:
    int size;
    HexGraph graph;
};

#endif