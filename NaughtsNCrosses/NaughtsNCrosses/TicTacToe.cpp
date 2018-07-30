#include "TicTacToe.h"


NaughtsNCrosses::NaughtsNCrosses()
{
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			h_2DArray[x][y] = 0;
		}
	}

	player = 1;
	playerToken = 'X';
}

NaughtsNCrosses::~NaughtsNCrosses()
{

}

bool NaughtsNCrosses::isCharValid(char c) const
{
	char temp = toupper(c);
	return (temp == 'A' || temp == 'B' || temp == 'C');
}

bool NaughtsNCrosses::isIntValid(unsigned int i) const
{
	return (0 < i && i <= 3);
}

bool NaughtsNCrosses::isSlotEmpty(unsigned int x, unsigned int y) const
{
	char temp;
	y -= 1;
	if (h_2DArray[x][y] == 0)
		return true;
	else
	{
		std::cout << "Coordinate is full!\n"; 
		std::cout << std::endl;
		system("pause");
		return false;
	}
}

unsigned int NaughtsNCrosses::getPlayer()
{
	return player;
}

void NaughtsNCrosses::input()
{
	char x = 0;
	unsigned int y = 0;

	do
	{
		drawBoard();
		std::cout << "Player " << playerToken << " Turn: (x, y)\n";
		std::cout << "x -> "; std::cin >> x;  std::cin.sync();
		while (!isCharValid(x))
		{
			drawBoard();
			std::cout << "Player " << playerToken << " Turn: (x, y)\n";
			std::cout << "Invalid coordinate x!\n";
			std::cout << "x -> "; std::cin >> x; std::cin.sync();
		}
		drawBoard();
		std::cout << "Player " << playerToken << " Turn: (" << (char)toupper(x) << ", y)\n";
		std::cout << "y -> "; std::cin >> y;
		while (!isIntValid(y))
		{
			drawBoard();
			std::cout << "Player " << playerToken << " Turn: (" << (char)toupper(x) << ", y)\n";
			std::cout << "Invalid coordinate y!\n";
			std::cout << "y -> "; std::cin >> y;
		} 
		drawBoard();
		std::cout << "Player " << playerToken << " Turn: (" << (char)toupper(x) << ", " << y << ")\n";
	} while (!isSlotEmpty(toInt(x), y));

	h_2DArray[toInt(x)][y - 1] = player;
}

bool NaughtsNCrosses::checkIfWin(unsigned int player)
{
	for (int row = 0; row < 3; ++row)
	{
		if (h_2DArray[row][0] == player && h_2DArray[row][1] == player && h_2DArray[row][2] == player)
			return true;
	}
	for (int column = 0; column < 3; ++column)
	{
		if (h_2DArray[0][column] == player && h_2DArray[1][column] == player && h_2DArray[2][column] == player)
			return true;
	}
	if (h_2DArray[0][0] == player && h_2DArray[1][1] == player && h_2DArray[2][2] == player)
		return true;
	else if (h_2DArray[0][2] == player && h_2DArray[1][1] == player && h_2DArray[2][0] == player)
		return true;
	return false;
}

char NaughtsNCrosses::toSymbol(unsigned int x)
{
	return "ABC"[x - 1];
}

int NaughtsNCrosses::toInt(char x)
{
	x = toupper(x);
	return x - 'A';
}

void NaughtsNCrosses::switchTurn()
{
	if (player == 1)
	{
		player++;
		playerToken = 'O';
	}
	else if (player == 2)
	{
		player--;
		playerToken = 'X';
	}
}

void NaughtsNCrosses::win()
{
	drawBoard();
	std::cout << "Player " << playerToken << " Wins!\n";
}

void NaughtsNCrosses::drawBoard()
{
	system("cls");
	
	std::cout << std::endl;
	std::cout << "    1 2 3\n";
	
	for (int x = 0; x < 3; ++x)
	{
		std::cout << "  " << toSymbol(x + 1);
		for (int y = 0; y < 3; ++y)
		{
			int checkValue = h_2DArray[x][y];
			switch (checkValue)
			{
			case 0:
				std::cout << "  ";
				break;
			case 1:
			{
				std::cout << " X";
				break;
			}
			case 2:
			{
				std::cout << " O";
				break;
			}
			default:
				std::cout << h_2DArray[x][y] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
