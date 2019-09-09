#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 3
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define NOT_OVER 0
#define WIN 1
#define DRAW 2

#define get_symbol(player) player == 1 ? PLAYER_1 : PLAYER_2

void game();
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int *get_player_move(int player, char board[BOARD_SIZE][BOARD_SIZE]);
void flush_input_buffer();
bool is_valid(char move, char board[BOARD_SIZE][BOARD_SIZE]);
void get_move_coordinates(char move, int *coordinates);
void update_board(int x, int y, char symbol, char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], int player);