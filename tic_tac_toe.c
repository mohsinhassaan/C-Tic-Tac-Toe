#include <stdio.h>
#include <stdbool.h>

void game();
void initialize_board(char board[3][3]);
void print_board(char board[3][3]);
void get_move(int player, char board[3][3]);
void update_board(int x, int y, char symbol, char board[3][3]);
bool is_valid(int x, int y, char board[3][3]);
int check_win(char board[3][3], int player);

int main(void)
{
    char again = 'y';
    do
    {
        game();
        while ((getchar()) != '\n')
            ;
        do
        {
            printf("Would you like to play again (y/n)? ");
            scanf("%c", &again);
            printf("\n");
        } while (again != 'y' && again != 'n');

    } while (again == 'y');
}

void game()
{
    int over = 0;

    int player = 2;

    char board[3][3];
    initialize_board(board);

    while (!over)
    {
        player = player == 1 ? 2 : 1;
        print_board(board);
        get_move(player, board);
        over = check_win(board, player);
        printf("\n――――――――――――――――――――――――――――――――――――――――――――――\n\n");
    }
    if (over == 1)
    {
        print_board(board);
        printf("Player %d wins!\n", player);
    }
    else if (over == 2)
        printf("Draw!\n");
}

void initialize_board(char board[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    }
}

void print_board(char board[3][3])
{
    printf("      0    1    2\n     ―――――――――――――\n");
    for (int i = 0; i < 3; ++i)
    {
        printf("%d ｜ ", i);
        for (int j = 0; j < 3; ++j)
        {
            printf(" %c", board[i][j]);
            if (j != 2)
                printf(" ｜");
        }
        printf("\n     ");
        if (i != 2)
            printf("―――――――――――――\n");
    }
}

void get_move(int player, char board[3][3])
{
    char symbol = player == 1 ? 'x' : 'o';

    printf("Player %d's move\n", player);
    printf("Where would you like to put your (%c)?\n", symbol);

    int x, y;

    do
    {
        printf("X coordinate: ");
        scanf("%d", &x);

        printf("Y coordinate: ");
        scanf("%d", &y);
    } while (!is_valid(x, y, board));

    update_board(x, y, symbol, board);
}

void update_board(int x, int y, char symbol, char board[3][3])
{
    board[y][x] = symbol;
}

bool is_valid(int x, int y, char board[3][3])
{
    if (x >= 0 && x <= 2 && y >= 0 && y <= 2)
    {
        if (board[y][x] == ' ')
            return true;
        else
            return false;
    }
    else
        return false;
}

int check_win(char board[3][3], int player)
{
    int filled = 0;

    char symbol = player == 1 ? 'x' : 'o';

    // Check top-left - bottom-right diagonal
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;

    // Check top-right - bottom-left diagonal
    else if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;

    else
    {
        for (int i = 0; i < 3; ++i)
        {
            // Check horizontal
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
                return 1;
            // Check vertical
            else if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
                return 1;
        }
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != ' ')
                ++filled;

    if (filled == 9)
        return 2;

    return false;
}