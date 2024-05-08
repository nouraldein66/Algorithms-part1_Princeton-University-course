#include "../include/BoardGame_Classes.hpp"

FivexFive_Tic_Tac_Toe::FivexFive_Tic_Tac_Toe() {
    n_rows = n_cols = 5;
    n_moves = 0;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}


bool FivexFive_Tic_Tac_Toe::update_board(int x, int y, char symbol) {
    if(x < 0 || x > 5 || y < 0 || y > 5 || board[x][y] != 0)
        return false;
    else{
        board[x][y] = toupper(symbol);
        n_moves++;
        return true;
    }
}

void FivexFive_Tic_Tac_Toe::display_board() {
    for (int i=0; i < 5; ++i) {
        cout << "\n| ";
        for (int j = 0; j<5; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(4) << board [i][j] << " |";
        }
        cout << "\n---------------------------------------------------------";
    }
    cout << endl;
}

int FivexFive_Tic_Tac_Toe::count_threes(char symbol) {
    int countX = 0, countO = 0;
    //horizontal counting
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2]){
                if(board[i][j] == 'X')
                    countX++;
                if(board[i][j] == 'O')
                    countO++;
            }

        }
    }
    //vertical counting
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j]){
                if(board[i][j] == 'X')
                    countX++;
                if(board[i][j] == 'O')
                    countO++;
            }

        }
    }

    //diagonal counting
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {

            if(j <= 2){ //right diagonals only
                if(board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2]){
                    if(board[i][j] == 'X')
                        countX++;
                    if(board[i][j] == 'O')
                        countO++;
                }

            }

            if(j >= 2){     //left diagonals
                if(board[i][j] == board[i+1][j-1] && board[i+1][j-1] == board[i+1][j-2]){
                    if(board[i][j] == 'X')
                        countX++;
                    if(board[i][j] == 'O')
                        countO++;
                }

            }
        }
    }

    if(symbol == 'X')
        return countX;
    else
        return countO;
}

bool FivexFive_Tic_Tac_Toe::is_winner() {
    if(!game_is_over())
        return false;
    int ansX = count_threes('X');
    int ansO = count_threes('O');
    if(ansX > ansO){
        return true;
    }
    return false;
}

bool FivexFive_Tic_Tac_Toe::is_draw() {
    if(count_threes('X') == count_threes('O'))
        return true;
    return false;
}

bool FivexFive_Tic_Tac_Toe::game_is_over() {
    return n_moves >= 24;
}
