#include <iostream>
#include <unordered_map>

#include "HexGraph.hpp"
#include "HexBoard.hpp"
#include "MonteCarloAI.hpp"

using namespace std;

#ifndef GAME_H
#define GAME_H

class Game {
  public:
    Game(int size=9, bool ai=false, int num_trials=1000);
    void start();
    void next(bool swap_move, int i, int j);
    void w_start(int i, int j);
    void b_start(bool swap_move);
    void w_turn(int i, int j);
    void b_turn(int i, int j);
    pair<TurnType, vector<pair<HexTile, vector<int>>>> get_game_state();

  private:
    int size;
    HexBoard board;
    pair<int, int> first_move;
    TurnType turn;
    MonteCarloAI * agent;
};

#endif