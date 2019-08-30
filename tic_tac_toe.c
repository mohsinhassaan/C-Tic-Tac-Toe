#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 3
#define PLAYER_1 'x'
#define PLAYER_2 'o'
#define NOT_OVER 0
#define WIN 1
#define DRAW 2

void game();
void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void get_move(int player, char board[BOARD_SIZE][BOARD_SIZE]);
void flush_input_buffer();
bool is_valid(char move, char board[BOARD_SIZE][BOARD_SIZE]);
void get_move_coordinates(char move, int *coordinates);
void update_board(int x, int y, char symbol, char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], int player);

int main(void)
{
    char again = 'y';
    do
    {
        game();
        do
        {
            printf("Would you like to play again (y/n)? ");
            again = getchar();
            flush_input_buffer();
            printf("\n");
        } while (again != 'y' && again != 'n');

    } while (again == 'y');
}

void game()
{
    int over = NOT_OVER;

    int player = 2;

    char board[BOARD_SIZE][BOARD_SIZE];
    initialize_board(board);

    while (over == NOT_OVER)
    {
        player = player == 1 ? 2 : 1;
        print_board(board);
        get_move(player, board);
        over = check_win(board, player);
        printf("\n――――――――――――――――――――――――――――――――――――――――――――――\n\n");
    }
    if (over == WIN)
    {
        print_board(board);
        printf("\nPlayer %d wins!\n", player);
    }
    else if (over == DRAW)
    {
        print_board(board);
        printf("\nDraw!\n");
    }
}

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int k = 1;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            board[i][j] = '0' + k++;
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf(" %c", board[i][j]);
            if (j != 2)
                printf(" ｜");
        }
        printf("\n");
        if (i != 2)
            printf("―――――――――――――\n");
    }
}

void get_move(int player, char board[BOARD_SIZE][BOARD_SIZE])
{
    char move, symbol = player == 1 ? PLAYER_1 : PLAYER_2;

    printf("\nPlayer %d's move\n", player);

    do
    {
        printf("Where would you like to put your (%c)? ", symbol);
        move = getchar();
        flush_input_buffer();
    } while (!is_valid(move, board));

    int coordinates[2];

    get_move_coordinates(move, coordinates);

    update_board(coordinates[0], coordinates[1], symbol, board);
}

void flush_input_buffer()
{
    char c;
    while ((c = getchar()) != '\n')
        ;
}

bool is_valid(char move, char board[BOARD_SIZE][BOARD_SIZE])
{
    if (move <= '0' && move > '9')
        return false;

    int coordinates[2];

    get_move_coordinates(move, coordinates);

    if (coordinates[0] >= 0 && coordinates[0] <= 2 && coordinates[1] >= 0 && coordinates[1] <= 2)
    {
        char point = board[coordinates[1]][coordinates[0]];
        if (point != PLAYER_1 && point != PLAYER_2)
            return true;
        else
            return false;
    }
    else
        return false;
}

void get_move_coordinates(char move, int *coordinates)
{
    int int_move = move - '0';

    if (int_move <= 3)
    {
        coordinates[0] = int_move - 1;
        coordinates[1] = 0;
    }
    else if (int_move <= 6)
    {
        coordinates[0] = int_move - 4;
        coordinates[1] = 1;
    }
    else
    {
        coordinates[0] = int_move - 7;
        coordinates[1] = 2;
    }
}

void update_board(int x, int y, char symbol, char board[BOARD_SIZE][BOARD_SIZE])
{
    board[y][x] = symbol;
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], int player)
{
    int filled = 0;

    char symbol = player == 1 ? PLAYER_1 : PLAYER_2;

    // Check top-left - bottom-right diagonal
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return WIN;

    // Check top-right - bottom-left diagonal
    else if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return WIN;

    else
    {
        for (int i = 0; i < 3; ++i)
        {
            // Check horizontal
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
                return WIN;
            // Check vertical
            else if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
                return WIN;
        }
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == PLAYER_1 || board[i][j] == PLAYER_2)
                ++filled;

    if (filled == 9)
        return DRAW;

    return NOT_OVER;
}