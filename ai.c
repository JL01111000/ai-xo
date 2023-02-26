#include "globals.h"

struct Move {
    int row;
    int col;
};

int evaluate_game_state(char game_board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2]) {
            if (game_board[i][0] == 'X') {
                return 10;
            } else if (game_board[i][0] == 'O') {
                return -10;
            }
        }
    }
    for (int j = 0; j < 3; j++) {
        if (game_board[0][j] == game_board[1][j] && game_board[1][j] == game_board[2][j]) {
            if (game_board[0][j] == 'X') {
                return 10;
            } else if (game_board[0][j] == 'O') {
                return -10;
            }
        }
    }
    if (game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) {
        if (game_board[0][0] == 'X') {
            return 10;
        } else if (game_board[0][0] == 'O') {
            return -10;
        }
    }
    if (game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]) {
        if (game_board[0][2] == 'X') {
            return 10;
        } else if (game_board[0][2] == 'O') {
            return -10;
        }
    }
    return 0;
}

struct Move find_best_move(char game_board[3][3]) {
    struct Move best_move;
    best_move.row = -1;
    best_move.col = -1;
    int best_score = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game_board[i][j] == ' ') {
                game_board[i][j] = 'X';
                int score = evaluate_game_state(game_board);
                game_board[i][j] = ' ';
                if (score > best_score) {
                    best_score = score;
                    best_move.row = i;
                    best_move.col = j;
                }
            }
        }
    }
    return best_move;
}

void make_ai_move(char game_board[3][3]) {
    struct Move best_move = find_best_move(game_board);
    game_board[best_move.row][best_move.col] = 'O';
}