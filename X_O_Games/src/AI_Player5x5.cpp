#include "../include/BoardGame_Classes.hpp"
#include <bits/stdc++.h>
using namespace std;


AI_Player5x5::AI_Player5x5(char symbol, Board* board) : Player(symbol)
{
    this->name = "AI  Player";
    cout << "My names is " << name << endl;
    boardptr = board;
}

string AI_Player5x5::getString(vector<string>& t) {
    string s = "";
    for (int i = 0; i < boardptr->get_n_rows(); ++i) {
        for (int j = 0; j < boardptr->get_n_cols(); ++j) {
            if(t[i][j])
                s+=t[i][j];
            else
                s+='_';
        }
    }
    return s;
}
/*
 * The evaluating function is about evaluating the board we have
 * by setting scores for the moves that might lead to winning
 * like three-streak, two-streak and one-streak
 * we put a score for each streak, and sum for x and o, then calculate
 * the difference, this will help the computer to predict and estimate
 * the best move possible according to the information it got.
 */
int AI_Player5x5::evaluatingFunction(vector<string>& Board, bool maximizer){

    //calculating x's and o's winning conditions
    int countX = 0, countO = 0;
    if(boardptr->game_is_over()){
        cout << 0 << "\n";
        if(boardptr->is_draw())
            return 0;
        if(boardptr->is_winner()){
            return 1000;
        }
        else
            return -1000;
    }
    //horizontal counting
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            //empty cell condition
            if(!Board[i][j]) {
                //empty with two same symbols after it: will be considered a two-streak
                if(Board[i][j+1] == Board[i][j+2]) {
                    if(Board[i][j+1] == 'X')
                        countX+=6;
                    if(Board[i][j+1] == 'O')
                        countO+=6;
                }
                //two empty cells with a symbol in between: will be considered a one-streak
                if(!Board[i][j+2]) {
                    if(Board[i][j+1] == 'X')
                        countX++;
                    if(Board[i][j+1] == 'O')
                        countO++;
                }
                //two empty cells with a symbol after it: will be considered a one-streak
                if(!Board[i][j+1]) {
                    if(Board[i][j+2] == 'X')
                        countX++;
                    if(Board[i][j+2] == 'O')
                        countO++;
                }
            }

            //three-in-a-row counting
            else if(Board[i][j] == Board[i][j+1] && Board[i][j+1] == Board[i][j+2]){
                if(Board[i][j] == 'X')
                    countX+=12;
                if(Board[i][j] == 'O')
                    countO+=12;
            }
                //two in a row counting
            else if( (Board[i][j] == Board[i][j+1] && Board[i][j+2] == 0) ||
                     (Board[i][j] == Board[i][j+2] && Board[i][j+1] == 0)){
                if(Board[i][j] == 'X')
                    countX+=6;
                if(Board[i][j] == 'O')
                    countO+=6;
            }
                //one symbol with two empty cells after it
            else if(Board[i][j] == 'X' && Board[i][j+1] == 0 && Board[i][j+2] == 0)
                countX++;
            else if(Board[i][j] == 'O' && Board[i][j+1] == 0 && Board[i][j+2] == 0)
                countO++;
        }
    }
    //vertical counting
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            //empty cell condition
            if(!Board[i][j]) {
                //an empty cell with two same symbols after it: will be considered a two-streak
                if(Board[i+1][j] == Board[i+2][j]) {
                    if(Board[i+1][j] == 'X')
                        countX+=6;
                    if(Board[i+1][j] == 'O')
                        countO+=6;
                }
                //two empty cells with a symbol in between: will be considered a one-streak
                if(Board[i+2][j] == 0) {
                    if(Board[i+1][j] == 'X')
                        countX++;
                    if(Board[i+1][j] == 'O')
                        countO++;
                }
                //two empty cells with a symbol after it: will be considered a one-streak
                if(!Board[i+1][j]) {
                    if(Board[i+2][j] == 'X')
                        countX++;
                    if(Board[i+2][j] == 'O')
                        countO++;
                }
            }
                //three in a row counting
            else if (Board[i][j] == Board[i + 1][j] && Board[i + 1][j] == Board[i + 2][j]) {
                if (Board[i][j] == 'X')
                    countX += 12;
                if (Board[i][j] == 'O')
                    countO += 12;
            }
                //two in a row counting
            else if ((Board[i][j] == Board[i+1][j] && Board[i+2][j] == 0) ||
                     (Board[i][j] == Board[i+2][j] && Board[i+1][j] == 0)) {
                if (Board[i][j] == 'X')
                    countX += 6;
                if (Board[i][j] == 'O')
                    countO += 6;
            }
                //one symbol with two empty cells after it
            else if (Board[i][j] == 'X' && Board[i + 1][j] == 0 && Board[i + 2][j] == 0)
                countX++;
            else if (Board[i][j] == 'O' && Board[i + 1][j] == 0 && Board[i + 2][j] == 0)
                countO++;
        }
    }
    //Diagonal counting
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {

            if(j <= 2){ //right diagonals only
                //empty cell condition
                if(!Board[i][j]) {
                    if(Board[i+1][j+1] == Board[i+2][j+2]) {
                        if(Board[i+1][j+1] == 'X')
                            countX+=6;
                        if(Board[i+1][j+1] == 'O')
                            countO+=6;
                    }
                    //two empty cells with a symbol in between: will be considered a one-streak
                    if(Board[i+2][j+2] == 0) {
                        if(Board[i+1][j+1] == 'X')
                            countX++;
                        if(Board[i+1][j+1] == 'O')
                            countO++;
                    }
                    //two empty cells with a symbol after it: will be considered a one-streak
                    if(!Board[i+1][j+1]) {
                        if(Board[i+2][j+2] == 'X')
                            countX++;
                        if(Board[i+2][j+2] == 'O')
                            countO++;
                    }
                }
                    //three in a row
                else if(Board[i][j] == Board[i+1][j+1] && Board[i+1][j+1] == Board[i+2][j+2]){
                    if(Board[i][j] == 'X')
                        countX+=12;
                    if(Board[i][j] == 'O')
                        countO+=12;
                }
                    //two in a row
                else if( (Board[i][j] == Board[i+1][j+1] && Board[i+2][j+2] == 0) ||
                         (Board[i][j] == Board[i+2][j+2] && Board[i+1][j+1] == 0) ) {
                    if(Board[i][j] == 'X')
                        countX+=6;
                    if(Board[i][j] == 'O')
                        countO+=6;
                }
                    //one symbol with two empty cells after it
                else if(Board[i][j] == 'X' && Board[i+1][j+1] == 0 && Board[i+2][j+2] == 0)
                    countX++;
                else if(Board[i][j] == 'O' && Board[i+1][j+1] == 0 && Board[i+2][j+2] == 0)
                    countO++;

            }

            if(j >= 2){     //left diagonals
                //empty cell condition
                if(!Board[i][j]) {
                    //one empty cell with two same symbols after it: will be considered a two-streak
                    if(Board[i+1][j-1] == Board[i+2][j-2]) {
                        if(Board[i+1][j-1] == 'X')
                            countX+=6;
                        if(Board[i+1][j-1] == 'O')
                            countO+=6;
                    }
                    //two empty cells with a symbol in between: will be considered a one-streak
                    if(Board[i+2][j-2] == 0) {
                        if(Board[i+1][j-1] == 'X')
                            countX++;
                        if(Board[i+1][j-1] == 'O')
                            countO++;
                    }
                    //two empty cells with a symbol after it: will be considered a one-streak
                    if(!Board[i+1][j-1]) {
                        if(Board[i+2][j-2] == 'X')
                            countX++;
                        if(Board[i+2][j-2] == 'O')
                            countO++;
                    }
                }
                //three in a row
                else if(Board[i][j] == Board[i+1][j-1] && Board[i+1][j-1] == Board[i+2][j-2]){
                    if(Board[i][j] == 'X')
                        countX+=12;
                    if(Board[i][j] == 'O')
                        countO+=12;
                }
                    //two in a row
                else if( (Board[i][j] == Board[i+1][j-1] && Board[i+2][j-2] == 0) ||
                         (Board[i][j] == Board[i+2][j-2] && Board[i+1][j-1] == 0) ) {
                    if(Board[i][j] == 'X')
                        countX+=6;
                    if(Board[i][j] == 'O')
                        countO+=6;
                }
                    //one symbol with two empty cells after it
                else if(Board[i][j] == 'X' && Board[i+1][j-1] == 0 && Board[i+2][j-2] == 0)
                    countX++;
                else if(Board[i][j] == 'O' && Board[i+1][j-1] == 0 && Board[i+2][j-2] == 0)
                    countO++;
            }
        }
    }
    return maximizer ? -(countX - countO) : -(countO - countX);
}

map <string,int> dp;
int AI_Player5x5::minimax(vector<string> &v, int depth, int alpha, int beta, bool computer_turn) {
    bool pruned = false;
    if(depth == 0){
        return evaluatingFunction(v, computer_turn);
    }

    if(computer_turn){
        int maxEvaluation = -1e9;
        for (int i = 0; i < boardptr->get_n_rows(); ++i) {
            for (int j = 0; j < boardptr->get_n_cols(); ++j) {
                if(!v[i][j]){
                    v[i][j] = 'O';
                    int nextEval;
                    string s = getString(v);
                    if(dp.find(s) != dp.end()){
                        nextEval = dp[s];
                    }
                    else
                        nextEval = minimax(v,depth-1,alpha,beta,false);
                    v[i][j] = 0;
                    maxEvaluation = max(nextEval,maxEvaluation);
                    if(!pruned)
                        dp[s] = maxEvaluation;
                    alpha = max(alpha,maxEvaluation);
                    if(alpha >= beta){
                        pruned = true;
                        break;
                    }

                }
            }
        }
        return maxEvaluation;

    }

    if(!computer_turn){
        int minEvaluation = 1e9;
        for (int i = 0; i < boardptr->get_n_rows(); ++i) {
            for (int j = 0; j < boardptr->get_n_cols(); ++j) {
                if(!v[i][j]) {
                    int nextEval;
                    v[i][j] = 'X';
                    string s = getString(v);
                    if(dp.find(s) != dp.end()) {
                        nextEval = dp[s];
                    }
                    else
                        nextEval = minimax(v,depth-1,alpha,beta,true);
                    v[i][j] = 0;
                    minEvaluation = min(nextEval, minEvaluation);
                    beta = min(beta, minEvaluation);
                    if(!pruned)
                        dp[s] = minEvaluation;
                    if (alpha >= beta) {
                        pruned = true;
                        break;
                    }
                }
            }
        }
        return minEvaluation;
    }
}

void AI_Player5x5::get_move(int &x, int &y) {
    int  max_eval{(int)-1e9}, min_eval{(int) 1e9} , alpha{(int)-1e9} , beta{(int)1e9}, nextScore;
    vector<string> temp_board(boardptr->get_n_rows());

    temp_board = boardptr->get_board();
    for (int i = 0; i < boardptr->get_n_rows(); ++i) {
        for (int j = 0; j < boardptr->get_n_cols(); ++j) {
            if(!temp_board[i][j]){
                temp_board[i][j] = 'O';
                string s = getString(temp_board);
                if(dp.find(s) != dp.end())
                    nextScore = dp[s];
                else
                    nextScore = minimax(temp_board,5,alpha,beta,false);
                if(nextScore > max_eval){
                    max_eval = nextScore;
                    x = i;
                    y = j;
                }
                temp_board[i][j] = 0;
            }
        }
    }

}

