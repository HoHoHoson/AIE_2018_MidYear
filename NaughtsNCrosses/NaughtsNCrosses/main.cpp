#include "TicTacToe.h"


int main()
{
	int alphabet;
	NaughtsNCrosses ticTacToe;

	do
	{
		ticTacToe.input();
		if (!ticTacToe.checkIfWin(ticTacToe.getPlayer()))
			ticTacToe.switchTurn();
	} while (!ticTacToe.checkIfWin(ticTacToe.getPlayer()));
	ticTacToe.win();

	std::cout << std::endl;

	system("pause");
	return 0;
}