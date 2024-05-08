// Class definition for XO game classes
// Author:  Nour aldeen, Ahmed Alaa, Ahmed Abdelnabi
// Date:    16/12/2023
// Version: 1
#ifndef _BoardGame_CLASSES_H
#define _BoardGame_CLASSES_H

#include <bits/stdc++.h>

using namespace std;

class Board {
protected:
   int n_rows, n_cols;
   char** board;
   int  n_moves = 0;

public:
   // Return true  if move is valid and put it on board
   // within board boundaries in empty cell
   // Return false otherwise
   virtual bool update_board (int x, int y, char symbol) = 0;
   // Returns true if there is any winner
   // either X or O
   // Written in a complex way. DO NOT DO LIKE THIS.
   virtual bool is_winner() = 0;
   // Return true if all moves are done and no winner
   virtual bool is_draw() = 0;
   // Display the board and the pieces on it
   virtual void display_board() = 0;
   // Return true if game is over
   virtual bool game_is_over() = 0;
   //returns number of rows
   virtual int get_n_rows() = 0;
   //returns number of cols
   virtual int get_n_cols() = 0;
   //returns the board
   virtual vector<string> get_board() = 0;
};

///////////////////////////////////////////
// This class represents a 3 x 3 board
// used in X_O game
class X_O_Board: public Board {
public:
   X_O_Board ();
   bool update_board (int x, int y, char mark);
   void display_board();
   bool is_winner();
   bool is_draw();
   bool game_is_over();
    int get_n_rows(){return n_rows;}
    int get_n_cols(){return n_cols;}
    vector<string>get_board(){
        vector<string>ret(n_rows);
        for(int i{}; i < n_rows; i++)
            for(int j{}; j < n_cols; ++j)
                ret[i].push_back(board[i][j]);
        return ret;
    }
};

// This class represents a player who has
// a name and a symbol to put on board
class Player {
protected:
    string name;
    char symbol;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player (char symbol); // Needed for computer players
    Player (int order, char symbol);
    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
};

class Pyramic_X_O: public Board {
public:
    Pyramic_X_O();
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    int get_n_rows(){return n_rows;}
    int get_n_cols(){return n_cols;}
    vector<string>get_board(){
        vector<string>ret(1);
        for(int i{}; i < 1; i++)
            for(int j{}; j < 9; ++j)
                ret[i].push_back(board[i][j]);
        return ret;
    }
};

class AI_Pyramid_X_O_Player: public Pyramic_X_O, public Player {
protected:
    Pyramic_X_O *boardptr;

public:
    AI_Pyramid_X_O_Player(char symbol, Pyramic_X_O *board);
    void get_move(int &x, int &y, bool maximizer);
    int minimax(vector<string> board, int depth, int alpha, int beta, bool maximizer);
    string board_to_string(vector<string>board);
    void get_move(int &x, int &y);
};

// This class represents a 6 x 7 board
// used in collect_four game
class connectFourBoard:public Board {
    int lst_x, lst_y, lst_symbol;
public:
    connectFourBoard ();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    int get_n_rows(){return n_rows;}
    int get_n_cols(){return n_cols;}
    vector<string>get_board(){
        vector<string>ret(n_rows);
        for(int i{}; i < n_rows; i++)
            for(int j{}; j < n_cols; ++j)
                ret[i].push_back(board[i][j]);
        return ret;
    }
};

class AI_Player: public Player, public connectFourBoard{
protected:
    connectFourBoard *boardptr;

public:
    AI_Player(char symbol , connectFourBoard *board);
    void get_move(int&x , int& y, bool maximizer);
    int minimax(vector<string>board,int depth, int alpha, int beta, bool maximizer);
    string board_to_string(vector<string>board);
    void get_move(int& x, int& y);
};

class FivexFive_Tic_Tac_Toe: public Board{
public:
    //initialize the board
    FivexFive_Tic_Tac_Toe();
    //check if entered position is withing the boundaries or not
    bool update_board(int x, int y, char symbol) override;
    //display the board
    void display_board() override;
    //winning condition
    bool is_winner() override;
    //count the number of three-in-a-rows
    int count_threes(char symbol);
    //draw condition
    bool is_draw() override;
    //game over
    bool game_is_over() override;
    int get_n_rows(){
        return n_rows;
    }
    int get_n_cols(){
        return n_cols;
    }
    vector<string> get_board(){
        vector<string>ret(n_rows);
        for(int i{}; i < n_rows; i++)
            for(int j{}; j < n_cols; ++j)
                ret[i].push_back(board[i][j]);
        return ret;
    };


};



///////////////////////////////////////////

class AI_Player5x5 : public Player{
protected:
    Board* boardptr;
public:
    AI_Player5x5(char symbol, Board* board);
    void get_move(int&x, int&y);
    int minimax(vector<string> &v, int depth, int alpha, int beta, bool computer_turn);
    string getString(vector<string>& t);
    int evaluatingFunction(vector<string>& Board, bool maximizer);
    ~AI_Player5x5(){
        delete boardptr;
    }

};

///////////////////////////////////////////
// This class represents a random computer player
// that generates random positions x y (0 to 2)
// If invalid, game manager asks to regenerate
class RandomPlayer: public Player {
    protected:
        int first_dimension;
        int second_dimension;
    public:
        // Take a symbol and pass it to parent
        RandomPlayer (char symbol, int first_dimension, int second_dimension);
        // Generate a random move
        void get_move(int& x, int& y);
};

///////////////////////////////////////////
class GameManager {
    private:
        Board* boardPtr;
        Player* players[2];
    public:
        GameManager(Board*, Player* playerPtr[2]);
        void run();
        // This method creates board and players
        // It displays board
        // While True
        //   For each player
        //      It takes a valid move as x, y pair (between 0 - 2)
        //      It updates board and displays otit
        //      If winner, declare so and end
        //      If draw, declare so and end


};

class GameManager_5x5{
private:
    Board* boardPtr;
    Player* players[2];
public:
    GameManager_5x5(Board*, Player* playerPtr[2]);
    void run();

};



#endif
