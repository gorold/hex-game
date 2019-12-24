#include "Hex.hpp"

ostream& operator<<(ostream& out, vector<int> v) {
    for (auto i: v) {
        out << i << ' ';
    }
    return out;
}

void HexGraph::create_node(int i, int j) {
    int idx = size * i + j;

    edge_list[idx].first = HexTile::EMPTY;

    if (i == 0 && j == 0) {
        // Top left
        edge_list[idx].second.push_back(size * (i + 1) + j);
        edge_list[idx].second.push_back(size * i + (j + 1));
    } else if (i == size - 1 && j == size - 1) {
        // Bottom right
        edge_list[idx].second.push_back(size * (i - 1) + j);
        edge_list[idx].second.push_back(size * i + (j - 1));
    } else if (i == 0 && j == size - 1) {
        // Top right
        edge_list[idx].second.push_back(size * (i + 1) + j);
        edge_list[idx].second.push_back(size * i + (j - 1));
    } else if (i == size - 1 && j == 0) {
        // Bottom left
        edge_list[idx].second.push_back(size * (i - 1) + j);
        edge_list[idx].second.push_back(size * i + (j + 1));
    } else if (i == 0) {
        // Top row
        edge_list[idx].second.push_back(size * i + (j + 1));
        edge_list[idx].second.push_back(size * i + (j - 1));
        edge_list[idx].second.push_back(size * (i + 1) + (j - 1));
        edge_list[idx].second.push_back(size * (i + 1) + j);
    } else if (j == 0) {
        // Left column
        edge_list[idx].second.push_back(size * (i + 1) + j);
        edge_list[idx].second.push_back(size * (i - 1) + j);
        edge_list[idx].second.push_back(size * (i - 1) + (j + 1));
        edge_list[idx].second.push_back(size * i + (j + 1));
    } else if (i == size - 1) {
        // Bottom row
        edge_list[idx].second.push_back(size * i + (j + 1));
        edge_list[idx].second.push_back(size * i + (j - 1));
        edge_list[idx].second.push_back(size * (i - 1) + (j + 1));
        edge_list[idx].second.push_back(size * (i - 1) + j);
    } else if (j == size - 1) {
        // Right column
        edge_list[idx].second.push_back(size * (i + 1) + j);
        edge_list[idx].second.push_back(size * (i - 1) + j);
        edge_list[idx].second.push_back(size * (i + 1) + (j - 1));
        edge_list[idx].second.push_back(size * i + (j - 1));
    } else {
        // Internal tiles
        edge_list[idx].second.push_back(size * (i + 1) + j);
        edge_list[idx].second.push_back(size * i + (j + 1));
        edge_list[idx].second.push_back(size * (i - 1) + j);
        edge_list[idx].second.push_back(size * i + (j - 1));
        edge_list[idx].second.push_back(size * (i - 1) + (j + 1));
        edge_list[idx].second.push_back(size * (i + 1) + (j - 1));
    }
}

void HexGraph::create_src_dst() {
    vector<int> white_src, black_src;
    for (int i = 0; i < size; ++i) {
        // White source: source -> last row
        white_src.push_back(size * (size - 1) + i);
        // Black source: source -> first column
        black_src.push_back(size * i + 0);
        // White destination: first row -> destination
        edge_list[size * 0 + i].second.push_back(size * size + 2);
        // Black destination: last column -> destination
        edge_list[size * i + (size - 1)].second.push_back(size * size + 3);
    }
    edge_list.push_back(make_pair(HexTile::WHITE, white_src));
    edge_list.push_back(make_pair(HexTile::BLACK, black_src));
}

pair<HexTile, vector<int>> HexGraph::get(int idx) {
    return edge_list[idx];
}

pair<HexTile, vector<int>> HexGraph::get(int i, int j) {
    return edge_list[size * i + j];
}

void HexGraph::set(int i, int j, HexTile tile) {
    edge_list[size * i + j].first = tile;
}

ostream& operator<<(ostream& out, HexBoard& board) {
    for (int i = 0; i < board.size; ++i) {
        for (int k = 0; k < i; ++k) {
            out << ' ';
        }
        for (int j = 0; j < board.size; ++j) {
            board.graph.get(i, j);
            out << board.graph.get(i, j).first << ' ';
        }
        out << endl;
    }
    return out;
}

bool HexBoard::place_tile(int i, int j, HexTile tile) {
    if (graph.get(i, j).first == HexTile::EMPTY) {
        graph.set(i, j, tile);
        return true;
    } else {
        return false;
    }
}

bool HexBoard::is_connected(HexTile player) {
    int src, dst;
    if (player == HexTile::WHITE) {
        src = size * size + 0;
        dst = size * size + 2;
    } else if (player == HexTile::BLACK) {
        src = size * size + 1;
        dst = size * size + 3;
    } else {
        return false;
    }
    stack<int> dfs_stack;
    dfs_stack.push(src);
    while (dfs_stack.size() != 0) {
        pair<HexTile, vector<int>> current_node = graph.get(dfs_stack.top());
        dfs_stack.pop();
        for (int neighbour: current_node.second) {
            if (neighbour == dst) return true;
            else if (graph.get(neighbour).first == player) {
                dfs_stack.push(neighbour);
            }
        }
    }
    return false;
 }

int main()
{
    ;
}