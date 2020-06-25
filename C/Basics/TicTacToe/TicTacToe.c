
#include <stdio.h>
#include <stdbool.h>

#define C_BORAD_LENGTH 2
#define PLAYER1_SIGN 'X'
#define PLAYER2_SIGN 'O'

void PrintLine(int count) {
    for (size_t i = 0; i < count; i++)
    {
        printf("----");
    }
    printf("-\n");
}


void PrintRow(char row[C_BORAD_LENGTH]) {
    
    PrintLine(C_BORAD_LENGTH);

    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        printf("| %c ", row[i]);   
    }
    printf("|\n");
}

void PrintBoard(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
   
    for (size_t row = 0; row < C_BORAD_LENGTH; row++)
    {
         PrintRow(board[row]);
    }
    PrintLine(C_BORAD_LENGTH);
}


bool CheckRows(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
    uint8_t row_counter;
    char first_row;

    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        for (size_t j = 0; j < C_BORAD_LENGTH; j++)
        {
            // start of row
            if (j == 0) {
                first_row = board[i][j];
                row_counter = 1;
                continue;
            }
            
            // if char is like the start 
            if (board[i][j] == first_row) {
                row_counter += 1;
            }        
        }

        // all of the line is the same, so win
        if (row_counter == C_BORAD_LENGTH)
        {
            return true;
        } 
    }
    return false;
}

bool CheckColums(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
    uint8_t column_counter;
    char first_column;

    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        first_column = board[0][i];
        column_counter = 0;

        for (size_t j = 0; j < C_BORAD_LENGTH; j++)
        {
            
            // if char is like the start 
            if (board[j][i] == first_column) {
                column_counter += 1;
            }        
        }

        // all of the line is the same, so win
        if (column_counter == C_BORAD_LENGTH)
        {
            return true;
        } 
    }
    return false;
}

bool CheckCross(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
    uint8_t MainCrossCounter = 0, SecCrossCounter = 0;
    char MainFirstChar, SecFirstChar;

    MainFirstChar = board[0][0];
    SecFirstChar = board[0][C_BORAD_LENGTH - 1];
    
    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        // if char is like the start, in the main cross
        if (board[i][i] == MainFirstChar) {
            MainCrossCounter += 1;
        }

        // if char is like the start, in the secondery cross
        if (board[i][C_BORAD_LENGTH - (i + 1)] == SecFirstChar) {
            SecCrossCounter += 1;
        }

    }

    // all of the line is the same, so win
    if (MainCrossCounter == C_BORAD_LENGTH || SecCrossCounter == C_BORAD_LENGTH)
    {
        return true;
    }

    return false;
}

bool BoardFull(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
    uint8_t counter = 0;
    char current_symb;

    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        for (size_t j = 0; j < C_BORAD_LENGTH; j++)
        {
            current_symb = board[i][j];
            if (current_symb == PLAYER1_SIGN || current_symb == PLAYER2_SIGN)  {
                counter += 1;
            }
        }
        
    }
    return counter == (C_BORAD_LENGTH * C_BORAD_LENGTH);
}

bool GameWon(char board[C_BORAD_LENGTH][C_BORAD_LENGTH]) {
    return CheckColums(board) || CheckRows(board) || CheckCross(board);
}

char ALL_CHARS[] = {'1', '2', '3','4', '5', '6', '7', '8', '9', '0', '!', '$', '^', '&', '*', '=', '+', '(', ')', '#', '_', '.', '<', '>', 'a'};

int main() {
    char board[C_BORAD_LENGTH][C_BORAD_LENGTH] = {0};
    
    size_t index = 0;
    for (size_t i = 0; i < C_BORAD_LENGTH; i++)
    {
        for (size_t j = 0; j < C_BORAD_LENGTH; j++)
        {
            board[i][j] = ALL_CHARS[index++];
        }
        
    }
    

    printf("------------ TicTacTow ------------\n\n");
    uint8_t turn = 1;
    char move;
    bool MoveValid;
    bool GameEnd = false;

    while (!GameEnd)
    {
        printf("\n\nPlayer %d Turn:\n", turn);
        MoveValid = false;

        while (!MoveValid)
        {
            
            PrintBoard(board);
            printf("Enter a Move:\n");
            scanf(" %c", &move);

            for (size_t i = 0; i < C_BORAD_LENGTH; i++)
            {
                for (size_t j = 0; j < C_BORAD_LENGTH; j++)
                {
                    if (board[i][j] == move && move != PLAYER1_SIGN && move != PLAYER2_SIGN)
                    {
                        board[i][j] = turn == 1 ? PLAYER1_SIGN : PLAYER2_SIGN;
                        MoveValid = true;
                    }
                }
            }

            if (!MoveValid) {
                printf("Move Not Valid, Try Again\n\n", move);
            }
        }

        if (GameWon(board)) {
            GameEnd = true;
            printf("\n\nPlayer %d Won!\n", turn);
            PrintBoard(board); 
        }

        if (BoardFull(board)) {
            printf("\n\nIt's A tie!\n");
            PrintBoard(board);
            GameEnd = true;
        }
        turn = turn == 2 ? 1 : 2;
                   
    }        
    return 0;

}