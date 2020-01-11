#include "HexGraph.hpp"
#include "HexBoard.hpp"
#include "Game.hpp"

using namespace std;

int main()
{
    int board_size;
    cout << "Please choose your board size: "; cin >> board_size; cout << endl;
    Game game{board_size};
    game.start();
}