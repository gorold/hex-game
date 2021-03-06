#include "Game.hpp"

Game::Game(int size, bool ai, int num_trials) : size(size), board(size) {
    if (ai) {
        agent = new MonteCarloAI(size, num_trials);
    }
}

void Game::start() {
    turn = TurnType::W_TURN;
    bool w_win = false, b_win = false;
    while (!(w_win || b_win)) {
        if (!(agent != nullptr && turn == TurnType::B_TURN))
            cout << board;
        int i, j;
        bool swap_move;
        switch (turn) {
            // case TurnType::W_START:
            //     cout << "White start, please choose a tile to play." << endl;
            //     cout << "i: "; cin >> i;
            //     cout << "j: "; cin >> j;
            //     break;
            // case TurnType::B_START:
            //     cout << "Black start, would you like to swap with White? (1/0)" << endl;
            //     cin >> swap_move;
            //     break;
            case TurnType::W_TURN:
                cout << "White turn, please choose a tile to play." << endl;
                cout << "i: "; cin >> i;
                cout << "j: "; cin >> j;
                break;
            case TurnType::B_TURN:
                if (agent == nullptr) {
                    cout << "Black turn, please choose a tile to play." << endl;
                    cout << "i: "; cin >> i;
                    cout << "j: "; cin >> j;
                } else {
                    pair<TurnType, vector<pair<HexTile, vector<int>>>> game_state = get_game_state();
                    int agent_move = agent -> get_agent_move(game_state.first, game_state.second);
                    i = agent_move / size;
                    j = agent_move % size;
                }
                break;
                
        }
        next(swap_move, i, j);
        w_win = board.is_connected(HexTile::WHITE);
        b_win = board.is_connected(HexTile::BLACK);
    }
    cout << board << endl;
    if (w_win) {
        cout << "Congratulations, White wins!" << endl;
    } else if (b_win) {
        cout << "Congratulations, Black wins!" << endl;
    }
}

void Game::next(bool swap_move, int i, int j) {
    switch (turn) {
        case TurnType::W_START:
            w_start(i, j);
            break;
        case TurnType::B_START:
            b_start(swap_move);
            break;
        case TurnType::W_TURN:
            w_turn(i, j);
            break;
        case TurnType::B_TURN:
            b_turn(i, j);
            break;
    }
}

void Game::w_start(int i, int j) {
    this -> first_move = make_pair(i, j);
    bool valid_move = board.place_tile(i, j, HexTile::WHITE);
    if (valid_move) {
        turn = TurnType::B_START;
    } else {
        cout << "Not a valid move." << endl;
    }
    
}

void Game::b_start(bool swap_move) {
    if (swap_move == true) {
        board.replace_tile(first_move.first, first_move.second);
        turn = TurnType::W_TURN;
    } else {
        turn = TurnType::B_TURN;
    }
}

void Game::w_turn(int i, int j) {
    bool valid_move = board.place_tile(i, j, HexTile::WHITE);
    if (valid_move) {
        turn = TurnType::B_TURN;
    } else {
        cout << "Not a valid move." << endl;
    }
}

void Game::b_turn(int i, int j) {
    bool valid_move = board.place_tile(i, j, HexTile::BLACK);
    if (valid_move) {
        turn = TurnType::W_TURN;
    } else {
        cout << "Not a valid move." << endl;
    }
}

pair<TurnType, vector<pair<HexTile, vector<int>>>> Game::get_game_state() {
    return make_pair(turn, board.get_edge_list());
}