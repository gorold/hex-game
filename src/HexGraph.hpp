#include <iostream>
#include <vector>

using namespace std;

#ifndef HEXGRAPH_H
#define HEXGRAPH_H

enum class HexTile : unsigned short int {EMPTY, WHITE, BLACK};
ostream& operator<<(ostream& out, HexTile tile);

class HexGraph {
  public:
    HexGraph(int size);
    pair<HexTile, vector<int>> get(int idx);
    pair<HexTile, vector<int>> get(int i, int j);
    void set(int i, int j, HexTile tile);
    
  protected:
    int size;
    vector<pair<HexTile, vector<int>>> edge_list;
    void create_node(int i, int j);
    void create_src_dst();
};

#endif