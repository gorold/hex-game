#include "MonteCarloAI.hpp"

MonteCarloAI::MonteCarloAI(int size, int num_trials) : size(size), num_trials(num_trials) {
    random_device rd;
    this -> g = mt19937(rd());
};

int MonteCarloAI::get_agent_move(const TurnType& turn, const vector<pair<HexTile, vector<int>>>& edge_list) {
    vector<int> empty_tiles;
    vector<HexTile> results = vector<HexTile>(size * size);
    vector<int> num_wins = vector<int>(size * size);
    HexTile current_player;

    if (turn == TurnType::W_START || turn == TurnType::W_TURN) {
        current_player = HexTile::WHITE;
    } else {
        current_player = HexTile::BLACK;
    }

    for (int i = 0; i < size * size; ++i) {
        if (edge_list[i].first == HexTile::EMPTY) {
            empty_tiles.push_back(i);
        } else if (edge_list[i].first == HexTile::WHITE) {
            results[i] = HexTile::WHITE;
        } else if (edge_list[i].first == HexTile::BLACK) {
            results[i] = HexTile::BLACK;
        }
    }

    for (int i = 0; i < this -> num_trials; ++i) {
        pair<int, bool> trial_result = execute_trial(empty_tiles, current_player, edge_list, results);
        num_wins[trial_result.first] += trial_result.second;
    }
    return distance(num_wins.begin(), max_element(num_wins.begin(), num_wins.end()));
}

pair<int, bool> MonteCarloAI::execute_trial(
    vector<int> empty_tiles, 
    HexTile current_player, 
    const vector<pair<HexTile, 
    vector<int>>>& edge_list, vector<HexTile>& results) 
{
    split_tiles(empty_tiles, current_player, results);
    int move = empty_tiles[0];
    return make_pair(move, current_player == get_winner(results, edge_list));
}

void MonteCarloAI::split_tiles(
      vector<int>& empty_tiles, 
      const HexTile& current_player,
      vector<HexTile>& results)
{
    shuffle(empty_tiles.begin(), empty_tiles.end(), this -> g);
    HexTile opponent;
    if (current_player == HexTile::WHITE) {
        opponent = HexTile::BLACK;
    } else {
        opponent = HexTile::WHITE;
    }
    int midpoint = empty_tiles.size() / 2;
    for (int i = 0; i < empty_tiles.size(); ++i) {
        int tile = empty_tiles[i];
        if (i <= midpoint) {
            results[tile] = current_player;
        } else {
            results[tile] = opponent;
        }
    }
}

HexTile MonteCarloAI::get_winner(const vector<HexTile>& results, const vector<pair<HexTile, vector<int>>>& edge_list) {

    int src = size * size + 0;
    int dst = size * size + 2;

    stack<int> dfs_stack;
    dfs_stack.push(src);
    unordered_set<int> visited;
    while (!dfs_stack.empty()) {
        vector<int> current_neighbours = edge_list[dfs_stack.top()].second;
        visited.insert(dfs_stack.top());
        dfs_stack.pop();
        for (int neighbour: current_neighbours) {
            auto itr = visited.find(neighbour);
            if (itr != visited.end()) continue;
            if (neighbour == dst) return HexTile::WHITE;
            else if (results[neighbour] == HexTile::WHITE) dfs_stack.push(neighbour);
        }
    }
    return HexTile::BLACK;
}


