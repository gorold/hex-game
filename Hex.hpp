#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

enum class HexTile : unsigned short int {EMPTY, WHITE, BLACK};

ostream& operator<<(ostream& out, HexTile tile) {
    if (tile == HexTile::EMPTY) {
        out << 'O';
    } else if (tile == HexTile::WHITE) {
        out << 'W';
    } else if (tile == HexTile::BLACK) {
        out << 'B';
    }
    return out;
}

class HexGraph {
  public:
    HexGraph(int size) {
        this -> size = size;
        edge_list.resize(size * size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                create_node(i, j);
            }
        }
        create_src_dst();
    }

    pair<HexTile, vector<int>> get(int idx);
    pair<HexTile, vector<int>> get(int i, int j);
    void set(int i, int j, HexTile tile);

  protected:
    int size;
    vector<pair<HexTile, vector<int>>> edge_list;
    void create_node(int i, int j);
    void create_src_dst();
};

class HexBoard {
  public:
    HexBoard(int size) : graph(size) {
        this -> size = size;
    }

    bool place_tile(int i, int j, HexTile tile);
    bool is_connected(HexTile player);
    friend ostream& operator<<(ostream& out, HexBoard& board);
    
    
  private:
    int size;
    HexGraph graph;
};