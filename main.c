#include <stdio.h>

char board[3][3];

void initBoard()
{
    char num = '1';

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = num++;
        }
    }
}

void printBoard()
{
    printf("\n");

    for(int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c \n",
               board[i][0],
               board[i][1],
               board[i][2]);

        if(i < 2)
            printf("---|---|---\n");
    }

    printf("\n");
}

int isMovesLeft()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != 'X' &&
               board[i][j] != 'O')
            {
                return 1;
            }
        }
    }

    return 0;
}

int evaluate()
{
    for(int row = 0; row < 3; row++)
    {
        if(board[row][0] == board[row][1] &&
           board[row][1] == board[row][2])
        {
            if(board[row][0] == 'O')
                return 10;

            if(board[row][0] == 'X')
                return -10;
        }
    }

    for(int col = 0; col < 3; col++)
    {
        if(board[0][col] == board[1][col] &&
           board[1][col] == board[2][col])
        {
            if(board[0][col] == 'O')
                return 10;

            if(board[0][col] == 'X')
                return -10;
        }
    }

    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
    {
        if(board[0][0] == 'O')
            return 10;

        if(board[0][0] == 'X')
            return -10;
    }

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
    {
        if(board[0][2] == 'O')
            return 10;

        if(board[0][2] == 'X')
            return -10;
    }

    return 0;
}

int minimax(int depth, int isMax)
{
    int score = evaluate();

    if(score == 10)
        return score - depth;

    if(score == -10)
        return score + depth;

    if(!isMovesLeft())
        return 0;

    if(isMax)
    {
        int best = -1000;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] != 'X' &&
                   board[i][j] != 'O')
                {
                    char temp = board[i][j];

                    board[i][j] = 'O';

                    int value =
                        minimax(depth + 1, 0);

                    if(value > best)
                        best = value;

                    board[i][j] = temp;
                }
            }
        }

        return best;
    }
    else
    {
        int best = 1000;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] != 'X' &&
                   board[i][j] != 'O')
                {
                    char temp = board[i][j];

                    board[i][j] = 'X';

                    int value =
                        minimax(depth + 1, 1);

                    if(value < best)
                        best = value;

                    board[i][j] = temp;
                }
            }
        }

        return best;
    }
}

void computerMove()
{
    int bestVal = -1000;
    int bestRow = -1;
    int bestCol = -1;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != 'X' &&
               board[i][j] != 'O')
            {
                char temp = board[i][j];

                board[i][j] = 'O';

                int moveVal =
                    minimax(0, 0);

                board[i][j] = temp;

                if(moveVal > bestVal)
                {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestRow][bestCol] = 'O';
}

int playerMove()
{
    int choice;

    printf("Enter position (1-9): ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 9)
        return 0;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if(board[row][col] == 'X' ||
       board[row][col] == 'O')
    {
        return 0;
    }

    board[row][col] = 'X';
    return 1;
}

int main()
{
    char playAgain;

    do
    {
        initBoard();

        while(1)
        {
            printBoard();

            if(!playerMove())
            {
                printf("Invalid Move!\n");
                continue;
            }

            if(evaluate() == -10)
            {
                printBoard();
                printf("You Win!\n");
                break;
            }

            if(!isMovesLeft())
            {
                printBoard();
                printf("Draw!\n");
                break;
            }

            printf("Computer Thinking...\n");

            computerMove();

            if(evaluate() == 10)
            {
                printBoard();
                printf("Computer Wins!\n");
                break;
            }

            if(!isMovesLeft())
            {
                printBoard();
                printf("Draw!\n");
                break;
            }
        }

        printf("\nPlay Again? (Y/N): ");
        scanf(" %c", &playAgain);

    } while(playAgain == 'Y' ||
            playAgain == 'y');

    return 0;
}