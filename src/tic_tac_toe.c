#include <stdio.h>
#include <string.h>
#include <tic_tac_toe.h>

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
        player = player % 2 + 1;
        print_board(board);
        int *coordinates = get_player_move(player, board);
        update_board(coordinates[0], coordinates[1], get_symbol(player), board);
        free(coordinates);
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
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == PLAYER_1)
                printf(P1_COLOR);
            else if (board[i][j] == PLAYER_2)
                printf(P2_COLOR);
            printf(" %c" DEFAULT_COLOR, board[i][j]);
            if (j != 2)
                printf(" ｜");
        }
        printf("\n");
        if (i != 2)
            printf("―――――――――――――\n");
    }
}

int *get_player_move(int player, char board[BOARD_SIZE][BOARD_SIZE])
{
    char move, symbol = get_symbol(player);

    printf("\nPlayer %d's move\n", player);

    char *movestr = malloc(255 * sizeof(char));
    do
    {
        printf("Where would you like to put your (%c)? ", symbol);
        scanf("%s", movestr);
        move = strlen(movestr) == 1 ? atoi(movestr) + '0' : '0';
        flush_input_buffer();
    } while (!is_valid(move, board));

    free(movestr);
    int *coordinates = malloc(2 * sizeof(int));
    get_move_coordinates(move, coordinates);

    return coordinates;
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