#include "HexBoard.hpp"

HexBoard::HexBoard(int size) : size(size), graph(size) {
    ;
}

ostream& operator<<(ostream& out, HexBoard& board) {
    out << ' ';
    for (int i = 0; i < board.size; ++i) {
        out << i << ' ';
    }
    out << endl;
    for (int i = 0; i < board.size; ++i) {
        out << i << ' ';
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
    if (i >= size || j >= size) return false;

    if (graph.get(i, j).first == HexTile::EMPTY) {
        graph.set(i, j, tile);
        return true;
    } else {
        return false;
    }
}

bool HexBoard::remove_tile(int i, int j) {
    if (i >= size || j >= size) return false;

    if (graph.get(i, j).first == HexTile::EMPTY) {
        return false;
    } else {
        graph.set(i, j, HexTile::EMPTY);
        return true;
    }
}

bool HexBoard::replace_tile(int i, int j) {
    if (i >= size || j >= size) return false;

    HexTile tile = graph.get(i, j).first;
    if (tile == HexTile::WHITE) {
        graph.set(i, j, HexTile::BLACK);
    } else if (tile == HexTile::BLACK) {
        graph.set(i, j, HexTile::WHITE);
    } else {
        return false;
    }
    return true;
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
    unordered_set<int> visited;
    while (dfs_stack.size() != 0) {
        pair<HexTile, vector<int>> current_node = graph.get(dfs_stack.top());
        visited.insert(dfs_stack.top());
        dfs_stack.pop();
        for (int neighbour: current_node.second) {
            auto itr = visited.find(neighbour);
            if (itr != visited.end()) continue;
            if (neighbour == dst) return true;
            else if (graph.get(neighbour).first == player) {
                dfs_stack.push(neighbour);
            }
        }
    }
    return false;
 }

vector<pair<HexTile, vector<int>>> HexBoard::get_edge_list() {
    return this -> graph.get_edge_list();
}