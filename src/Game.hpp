#include <iostream>

#include "HexGraph.hpp"
#include "HexBoard.hpp"
#include "MonteCarloAI.hpp"

using namespace std;

#ifndef GAME_H
#define GAME_H

enum class TurnType : unsigned short int {W_START, B_START, W_TURN, B_TURN};

class Game {
  public:
    Game(int size=9, bool ai=false);
    void start();
    void next(bool swap_move, int i, int j);
    void w_start(int i, int j);
    void b_start(bool swap_move);
    void w_turn(int i, int j);
    void b_turn(int i, int j);

  private:
    HexBoard board;
    pair<int, int> first_move;
    TurnType turn;
    bool ai;
};

#endif