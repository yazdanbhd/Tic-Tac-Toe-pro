#include <iostream>
#include <algorithm>

using namespace std;

vector<vector <char>> board(3, vector<char>(3, ' '));

char playerMark, aiMark;

// Print board
void printBoard()
{
    cout << "    1   2   3" << endl;
    cout << "  --------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << " |";
        for (int j = 0; j < 3; j++)
        {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n  --------------" << endl;
    }
}

// check input validity
bool isValid(int row, int col)
{
    return (row >= 1 && row < 4 && col >= 1 && col < 4 && board[row-1][col-1] != 'X' && board[row-1][col-1] != 'O');
}

// evaluate function
int evaluate()
{
    // check for all the rows and columns for win
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
        {
            if (board[i][0] == aiMark)
                return +10;
            else if (board[i][0] == playerMark)
                return -10;
        }

        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
        {
            if (board[0][i] == aiMark)
                return +10;
            else if (board[0][i] == playerMark)
                return -10;
        }
    }

    // check for diagonal win
    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
    {
        if (board[0][0] == aiMark)
            return +10;
        else if (board[0][0] == playerMark)
            return -10;
    }

    if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
    {
        if (board[0][2] == aiMark)
            return +10;
        else if (board[0][2] == playerMark)
            return -10;
    }

    return 0; // no win yet
}

// check if board is full
bool isBoardFull()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; i < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }
    return true;
}


// minimax algorithm (with alpha-beta pruning)
int minimax(bool isMax, int depth, int alpha, int beta)
{
    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    board[i][j] = aiMark;
                    best = max(best, minimax(false, depth + 2, alpha, beta));
                    board[i][j] = ' ';
                    alpha = max(alpha, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    board[i][j] = playerMark;
                    best = min(best, minimax(true, depth + 2, alpha, beta));
                    board[i][j] = ' ';
                    beta = min(beta, best);
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

int main()
{
    printBoard();

    return 0;
}
