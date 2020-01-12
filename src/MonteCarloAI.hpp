#include <tuple>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <ctime>

#include "HexGraph.hpp"

using namespace std;

#ifndef MONTECARLOAI_H
#define MONTECARLOAI_H

enum class TurnType : unsigned short int {W_START, B_START, W_TURN, B_TURN};

class MonteCarloAI {
  public:
    MonteCarloAI(int size, int num_trials=1000);
    int get_agent_move(const TurnType& turn, const vector<pair<HexTile, vector<int>>>& edge_list);
    int get_random_tile(vector<int>& tiles);
    pair<int, bool> execute_trial(vector<int> empty_tiles, HexTile current_player, const vector<pair<HexTile, vector<int>>>& edge_list, vector<HexTile>& results);
    void split_tiles(
      vector<int>& empty_tiles, 
      const HexTile& current_player,
      vector<HexTile>& results);
    HexTile get_winner(const vector<HexTile>& results, const vector<pair<HexTile, vector<int>>>& edge_list);

  private:
    int size;
    int num_trials;
    mt19937 g;
};

#endif