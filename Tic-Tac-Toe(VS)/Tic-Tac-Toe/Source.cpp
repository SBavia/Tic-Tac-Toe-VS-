#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
void instructions();
char askYesNo(string question);
int askNumber(string question, int high=8, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void annouceWinner(char winner, char computer, char human);
int main()
{
	int move;
	const int NUM = 9;
	vector<char> board(NUM, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);
	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		system("cls");
		displayBoard(board);
		turn = opponent(turn);
	}
	annouceWinner(winner(board), computer, human);
	system("pause");
	return 0;
}
void instructions()
{
	cout << "Welcome to Tic-Tac-Toe.\nBoard:\n" << endl;
	cout << " 0 | 1 | 2\n";
	cout << "-----------\n";
	cout << " 3 | 4 | 5\n";
	cout << "-----------\n";
	cout << " 6 | 7 | 8\n";
	cout << "-----------\n";
	cout << "Good luck!\n";
}
char askYesNo(string question)
{
	char res;
	do
	{
		cout << question << "(y/n): \n";
		cin >> res;
	} while (res != 'y'&&res != 'n');
	return res;
}
int askNumber(string question, int high, int low)
{
	int num;
	do
	{
		cout << question << " (" << low << "-" << high << " ): ";
		cin >> num;
	} while (num > high || num < low);
	return num;
}
char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "You will be a X.\n";
		return 'X';
	}
	else
	{
		cout << "You will be a X.\n";
		return 'O';
	}
}
char opponent(char piece)
{
	if (piece == 'X')return 'O';
	else return 'X';
}
void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t"<<"---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8] << endl;
}
char winner(const vector<char>& board)
{
	const int WIN[8][3] =
	{ {0,1,2},
	{ 3,4,5 },
	{ 6,7,8 },
	{ 0,4,8 },
	{ 0,3,6 },
	{ 2,5,8 },
	{ 2,4,6 },
	{ 1,4,7 } };
	for (int row = 0; row < 8; row++)
	{
		if (((board[WIN[row][0]]) != EMPTY) && (board[WIN[row][0]] == board[WIN[row][1]])
			&& (board[WIN[row][1]] == board[WIN[row][2]]))
		{
			return board[WIN[row][0]];
		}
	}
	if (count(board.begin(), board.end(), EMPTY) == 0)return TIE;
	return NO_ONE;
}
inline bool isLegal(const vector<char>& board, int move)
{
	return (board[move] == EMPTY);
}
int humanMove(const vector<char>& board, char human)
{
	int move = askNumber("Where will you move?");
	while (!isLegal(board, move))
	{
		cout << "It's wrong.\n";
		askNumber("Where will you move?");
	}
	return move;
}
int computerMove(vector<char> board, char computer)
{
	int move = 0;
	bool found = false;
	while (!found&&move < 9)
	{
		if (isLegal(board, move))
		{
			board[move] = computer;
			found = winner(board)==computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			move++;
		}
	}
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found&&move < 9)
		{
			if (isLegal(board, move))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)++move;
		}
	}
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST[] = { 4,0,2,6,8,1,3,5,7 };
		while (!found&&i < 9)
		{
			move = BEST[i];
			if (isLegal(board, move))
			{
				found = true;
			}
			++i;
		}
	}
	return move;
}
void annouceWinner(char winner, char computer, char human)
{
	if(winner==computer||winner==human)cout << winner << "'s won!\n";
	else cout << "It's a tie.\n";
}