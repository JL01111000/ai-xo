#ifndef AI_H
#define AI_H

struct Move {
    int row;
    int col;
};

struct Move find_best_move(char game_board[3][3]);
int evaluate_game_state(char game_board[3][3]);
void make_ai_move(char game_board[3][3]);

#endif