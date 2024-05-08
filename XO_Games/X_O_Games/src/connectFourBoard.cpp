// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include"../include/BoardGame_Classes.hpp"

using namespace std;

connectFourBoard::connectFourBoard() {
    lst_x = lst_y = 0;
    lst_symbol = ' ';
    n_rows = 6;
    n_cols = 7;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

bool connectFourBoard::update_board(int x, int y, char mark) {
    // Only update if move is valid

    if (!(x < 0 || x > 5 || y < 0 || y > 6) && (board[x][y] == 0)) {
        bool isValid = (x == 5 || board[x + 1][y] != 0);
        if (isValid) {

        board[x][y] = toupper(mark);
        n_moves++;
        lst_x = x , lst_y = y ,lst_symbol = toupper(mark);
        return true;
        } else {
            return false;
        }
    }
    else
        return false;
}

void connectFourBoard::display_board() {
    for (int i: {0, 1, 2 , 3 , 4 , 5}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4,5,6,}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board [i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

bool connectFourBoard::is_winner() {
// horizontally
    for(int i = max(0 , lst_y - 3) ; i <= min(lst_y , 3) ; ++i)
    {

        for(int j{i} ; j < i + 4 ; ++j)
        {
            if(board[lst_x][j] != lst_symbol)
            {
                goto dist1;
            }
        }
        return 1;
        dist1:;
    }
// vertically
    for(int i = max(0 , lst_x - 3) ; i <= min(lst_x , 2) ; ++i)
    {

        for(int j{i} ; j < i + 4 ; ++j)
        {
            if(board[j][lst_y] != lst_symbol)
            {
                goto dist2;
            }
        }
        return 1;
        dist2:;
    }
// diagonally
    for(int i = lst_x - min(lst_x , lst_y) , j = lst_y - min(lst_x , lst_y) ; i <= min(lst_x , 2) && j <= min(lst_y , 3) ; ++i , ++j)
    {
        for(int k{} ; k < 4 ; k++)
        {
            if(board[i + k][j + k] != lst_symbol)
            {
                goto dist3;
            }
        }
        return 1;
        dist3:;
    }

    for(int i = lst_x + min(5 - lst_x , lst_y) , j = lst_y - min(5 - lst_x , lst_y) ; i >= max(lst_x , 3) && j <= min(lst_y , 3) ; --i , ++j)
    {
        for(int k{} ; k < 4 ; k++)
        {
            if(board[i - k][j + k] != lst_symbol)
            {
                goto dist4;
            }
        }
        return 1;
        dist4:;
    }

    return 0;
}

bool connectFourBoard::is_draw() {
    return n_moves == 42 && !is_winner();
}

bool connectFourBoard::game_is_over() {
    return  n_moves == 42;
}

int evaluate_window(vector<char> window, char player) {
    char opponent = (player == 'O') ? 'X' : 'O';
    int score = 0;

    for (char d : window) {
        if (d == player) {
            score += 1;
        } else if (d == opponent) {
            // If there is an opponent disc in the window, it's not a winning position for the player
            return 0;
        }
    }

    // Count player discs only
    if (score == 4) {
        return 100;
    } else if (score == 3) {
        return 5;
    } else if (score == 2) {
        return 2;
    }

    return 0;
}

int evaluate( vector<string> board, char player) {
    int score = 0;
    // Check horizontal
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            vector<char> window(board[row].begin() + col, board[row].begin() + col + 4);
            score += evaluate_window(window, player);
        }
    }

    // Check vertical
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 7; ++col) {
            vector<char> window;
            for (int i = 0; i < 4; ++i) {
                window.push_back(board[row + i][col]);
            }
            score += evaluate_window(window, player);
        }
    }

    // Check diagonal (positive slope)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            vector<char> window;
            for (int i = 0; i < 4; ++i) {
                window.push_back(board[row + i][col + i]);
            }
            score += evaluate_window(window, player);
        }
    }

    // Check diagonal (negative slope)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            vector<char> window;
            for (int i = 0; i < 4; ++i) {
                window.push_back(board[row + 3 - i][col + i]);
            }
            score += evaluate_window(window, player);
        }
    }
    return score;
}

AI_Player::AI_Player(char symbol, connectFourBoard *board) :Player(symbol)
{
    this->name = "AI  Player";
    cout << "My names is " << name << endl;
    boardptr = board;
}
string AI_Player::board_to_string(vector<string>board) {
    string ret = "";
    for(int i{}; i < boardptr->get_n_rows(); ++i)
        for(int j{}; j < boardptr->get_n_cols(); ++j)
            ret += (!board[i][j])? '_':board[i][j];
    return ret;

}
map<string, int> dp1;
int xx{};
int AI_Player::minimax(vector<string>board,int depth, int alpha, int beta, bool maximizer) {
//    cout<<xx<<'\n';
    string state = board_to_string(board);
//        cout << depth<<' '<<alpha<<' '<<beta<<' '<<maximizer<<' '<<state<<' '<< evaluate(board, maximizer? 'X' : 'O')<<'\n';
    if(dp1.find(state) != dp1.end()) {
        return dp1[state];
    }
    if(!depth)
    {
        ++xx;
        return  dp1[state] =  evaluate(board, maximizer? 'X' : 'O');
    }

    if(maximizer)
    {
        int max_value{-(int)1e9};
        for(int i{}; i < boardptr->get_n_rows(); ++i)
        {
            for(int j{}; j < boardptr->get_n_cols(); ++j)
            {
                if(!board[i][j] && (i == 5 || board[i + 1][j]))
                {
                    vector<string> temp_board = board;  // Create a deep copy
                    temp_board[i][j] = 'O';
                    int value = minimax(temp_board,depth - 1, alpha, beta, 0);
                    max_value = max(value , max_value);
                    alpha = max(alpha, value);
                    board[i][j] = 0;
                    if(beta <= alpha)
                        break;
                }

            }
        }
        return dp1[state] = max_value;
    }
    else
    {
        int min_value{(int)1e9};
        for(int i{}; i < boardptr->get_n_rows(); ++i)
        {
            for(int j{}; j < boardptr->get_n_cols(); ++j)
            {
                if(!board[i][j] && (i == 5 || board[i + 1][j]))
                {
                    vector<string> temp_board = board;  // Create a deep copy
                    temp_board[i][j] = 'X';
                    int value = minimax(temp_board,depth - 1, alpha, beta, 1);
                    min_value = min(value , min_value);
                    beta = min(beta, value);
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return  dp1[state] = min_value;
    }
}
void AI_Player::get_move(int &x, int &y, bool maximizer) {

    int max_eval = -(int)1e9;
    char symbol = (maximizer)? 'O' : 'X';
    vector<string>temp_board = boardptr->get_board();

//  for(auto i : dp2)cout<<i.first<<' '<<i.second<<'\n';
    for(int i{}; i < boardptr->get_n_rows(); ++i)
    {
        for(int j{}; j < boardptr->get_n_cols(); ++j)
        {
//            cout << max_eval<<'\n';
            if(!temp_board[i][j] && (i == 5 || temp_board[i + 1][j])){
                temp_board[i][j] = 'O';
                int score = minimax(temp_board ,7,-1e9,1e9,false);
//                cout << score<<'\n';
                temp_board[i][j] = 0;
                if(score > max_eval){
                    max_eval = score;
                    x = i;
                    y = j;
//                    cout << x << ' ' << y << '\n';
                }
            }

        }
    }

}

void AI_Player::get_move(int &x, int &y) {
    get_move(x, y , 1);

}





