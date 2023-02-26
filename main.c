#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "ai.h"

void run_game(void);
void selection_completed(void);

char game_board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

int games_played = 0;
int player_wins;
int ai_wins;
int games_tied;
char player_initials[3];

void display_game_header() {
    printf(" _______ _        _______           _______         \n");
    printf("|__   __(_)      |__   __|         |__   __|        \n");
    printf("   | |   _  ___     | | __ _  ___     | | ___   ___ \n");
    printf("   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\\n");
    printf("   | |  | | (__     | | (_| | (__     | | (_) |  __/\n");
    printf("   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\____ °·.¸.·°¯°·.¸.·°¯°·.¸.-> ╚» Ｂｙ ＪＬ «╝ >-.¸.·°¯°·.¸.·°¯°·.¸.·°(っ◔◡◔)っ\n\n");
}

void welcome_message() {
    printf("---------------------------------------------\n");
    printf("Welcome! Push the 'Enter' key to get started!\n");
    printf("---------------------------------------------\n\n");
}

void display_main_menu() {
    system("clear");
    display_game_header();

    printf("------------------------------\n");
    printf("MAIN MENU\n");
    printf("1. View The Game Instructions.\n");
    printf("2. Play The Game.\n");
    printf("3. Show Your Wins & Losses.\n");
    printf("4. Exit The Program.\n");
    printf("------------------------------\n\n");
}

int get_main_menu_choice() {
    int main_menu_choice;
    while (1) {
        printf("Enter the number associated with your desired choice (1-4): ");
        if (scanf("%d", &main_menu_choice) != 1 || main_menu_choice < 1 || main_menu_choice > 4) {
            display_main_menu();
            printf("Invalid input. ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else {
            break;
        }
    }
    return main_menu_choice;
}

char *get_player_initials() {
    printf("--------------------------------------------------\n");
    printf("You must enter your intitials before you can play.\n");
    printf("--------------------------------------------------\n");
    printf("\nEnter them here: ");
    while (scanf(" %c%c%*c", &player_initials[0], &player_initials[1]) != 2 || player_initials[0] == '\n' || player_initials[1] == '\n') {
        system("clear");
        display_game_header();
        printf("--------------------------------------------------\n");
        printf("You must enter your intitials before you can play.\n");
        printf("--------------------------------------------------\n");
        printf("\nInvalid input. Enter two letters: ");
        while (getchar() != '\n');
    }
    player_initials[2] = '\0';
    return player_initials;
}

int get_player_move() {
    int player_move;
    while (1) {
        printf("\n----------------------------------------------------------------\n");
        printf("Enter '1' to place your 'X' in the upper left corner.\n");
        printf("Enter '2' to place your 'X' in the middle of the top row.\n");
        printf("Enter '3' to place your 'X' in the upper right corner.\n");
        printf("Enter '4' to place your 'X' on the left side of the middle row.\n");
        printf("Enter '5' to place your 'X' in the middle of the middle row.\n");
        printf("Enter '6' to place your 'X' on the right side of the middle row.\n");
        printf("Enter '7' to place your 'X' in the bottom left corner.\n");
        printf("Enter '8' to place your 'X' in the middle of the bottom row.\n");
        printf("Enter '9' to place your 'X' in the bottom right corner.\n");
        printf("----------------------------------------------------------------\n");
        printf("\nEnter a number between 1 and 9: ");
        if (scanf("%d", &player_move) != 1 || player_move < 1 || player_move > 9) {
            printf("Invalid input. ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else {
            break;
        }
    }
    return player_move;
}

void update_game_board() {
    int player_move = get_player_move();
    switch (player_move) {
    case 1:
        game_board[0][0] = 'X';
        break;
    case 2:
        game_board[0][1] = 'X';
        break;
    case 3:
        game_board[0][2] = 'X';
        break;
    case 4:
        game_board[1][0] = 'X';
        break;
    case 5:
        game_board[1][1] = 'X';
        break;
    case 6:
        game_board[1][2] = 'X';
        break;
    case 7:
        game_board[2][0] = 'X';
        break;
    case 8:
        game_board[2][1] = 'X';
        break;
    case 9:
        game_board[2][2] = 'X';
        break;
    default:
        break;
    }
}

void display_board() {
    printf(" %c | %c | %c \n", game_board[0][0], game_board[0][1], game_board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", game_board[1][0], game_board[1][1], game_board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", game_board[2][0], game_board[2][1], game_board[2][2]);
}

int check_for_winner() {
    int winner = 0;

    for (int i = 0; i < 3; i++) {
        if (game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2]) {
            if (game_board[i][0] == 'X') {
                winner = 1;
            }
            else if (game_board[i][0] == 'O') {
                winner = 2;
            }
        }
    }

    for (int j = 0; j < 3; j++) {
        if (game_board[0][j] == game_board[1][j] && game_board[1][j] == game_board[2][j]) {
            if (game_board[0][j] == 'X') {
                winner = 1;
            }
            else if (game_board[0][j] == 'O') {
                winner = 2;
            }
        }
    }

    if (game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) {
        if (game_board[0][0] == 'X') {
            winner = 1;
        }
        else if (game_board[0][0] == 'O') {
            winner = 2;
        }
    }

    if (game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]) {
        if (game_board[0][2] == 'X') {
            winner = 1;
        }
        else if (game_board[0][2] == 'O') {
            winner = 2;
        }
    }

    int moves = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game_board[i][j] != ' ') {
                moves++;
            }
        }
    }
    if (moves == 9 && winner == 0) {
        winner = 3;
    }

    return winner;
}

void ai_turn_message() {
    printf("\nThe AI is thinking...\n");
    sleep(1);
    printf("The AI is thinking...\n");
    sleep(1);
    printf("The AI is thinking...\n");
    sleep(1);
}

void get_user_initiation() {
    while (getchar() != '\n');
    display_main_menu();
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void display_instructions() {
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("Hi! You will be playing against an AI in this Tic Tac Toe Program.\n");
    printf("\n• You will be X's and the AI will be O's.\n");
    printf("• You will alternate turns with the AI and each time it is your turn, you will be prompted to make a move.\n");
    printf("• The gameplay mechanics to make your move are as follows:\n");
    printf("\nEnter '1' to place your 'X' in the upper left corner.\n");
    printf("Enter '2' to place your 'X' in the middle of the top row.\n");
    printf("Enter '3' to place your 'X' in the upper right corner.\n");
    printf("Enter '4' to place your 'X' on the left side of the middle row.\n");
    printf("Enter '5' to place your 'X' in the middle of the middle row.\n");
    printf("Enter '6' to place your 'X' on the right side of the middle row.\n");
    printf("Enter '7' to place your 'X' in the bottom left corner.\n");
    printf("Enter '8' to place your 'X' in the middle of the bottom row.\n");
    printf("Enter '9' to place your 'X' in the bottom right corner.\n");
    printf("\nGood Luck!");
    printf("\n----------------------------------------------------------------------------------------------------------");
    selection_completed();
}

void show_wins_losses() {
    if (games_played == 0) {
        printf("--------------------------------------------------");
        printf("\nYou must play at least one game to view this page!");
        printf("\n--------------------------------------------------");
    }

    if (games_played > 0) {
        printf("----------\n");
        printf("Ties: %d\n", games_tied);
        printf("\n%s Wins: %d\n", player_initials, player_wins);
        printf("\nAI Wins: %d\n", ai_wins);
        printf("----------");
    }

    selection_completed();
}

void determine_second_menu() {
    int second_menu = get_main_menu_choice();
    switch (second_menu) {
    case 1:
        system("clear");
        display_game_header();
        display_instructions();
        break;
    case 2:
        run_game();
        break;
    case 3:
        system("clear");
        display_game_header();
        show_wins_losses();
        break;
    case 4:
        system("clear");
        exit(0);
        break;
    default:
        break;
    }
}

void selection_completed() {
    printf("\n------------------------------------------------\n");
    printf("Push the 'Enter' key to return to the main menu.\n");
    printf("------------------------------------------------\n\n");

    clear_input_buffer();
    get_user_initiation();
    determine_second_menu();
}

void run_game() {
    system("clear");
    display_game_header();

    if (games_played == 0) {
        char *player_initials = get_player_initials();
    }

    while (check_for_winner() == 0) {
        system("clear");
        display_game_header();
        display_board();
        update_game_board();
        system("clear");
        display_game_header();
        display_board();

        if (check_for_winner() == 0) {
            ai_turn_message();
            make_ai_move(game_board);
        }
    }

    system("clear");
    display_game_header();
    display_board();

    if (check_for_winner() == 1) {
        games_played++;
        player_wins++;
        printf("\nYou Win!!!\n");
    }

    if (check_for_winner() == 2) {
        games_played++;
        ai_wins++;
        printf("\nThe AI Won!\n");
    }

    if (check_for_winner() == 3) {
        games_played++;
        games_tied++;
        printf("\nIt's A Tie!\n");
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            game_board[i][j] = ' ';
        }
    }

    selection_completed();
}

int main() {
    system("clear");
    display_game_header();
    welcome_message();
    get_user_initiation();
    determine_second_menu();

    return 0;
}