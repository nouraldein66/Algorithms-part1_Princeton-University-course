#include "../include/BoardGame_Classes.hpp"
#include <iostream>
using namespace std;


GameManager_5x5::GameManager_5x5(Board* bPtr, Player* playerPtr[2] ) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager_5x5::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i:{0,1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board (x, y, players[i]->get_symbol())){
                players[i]->get_move(x,y);
            }
            boardPtr->display_board();

        }
    }

    if (boardPtr->is_draw()){
        cout << "Draw!\n";
        return;
    }
    if (boardPtr->is_winner()){
        cout << players[0]->to_string() << " wins";
    }
    else
        cout << players[1]->to_string() << " wins";
}
