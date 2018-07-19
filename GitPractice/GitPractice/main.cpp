#include <iostream>
#include <string>

std::string adj;
std::string verb;
std::string noun;
bool test;
std::string name;
bool login = false;
char choice;

void logon()
{
	system("cls");
	std::cout << "Please enter your name: ";
	std::cin >> name;
	system("cls");
}

int main() 
{
	do
	{
		logon();
		if (name == "Hoson" || name == "Andrew" || name == "Ed" || name == "Sam" || name == "Matt")
		{
			std::cout << "Welcome back " << name << "!\n";
			login = true;
			std::cout << std::endl;
			system("Pause");
		}
		else
		{
			std::cout << "<Error> User not recognised.\n";
			std::cout << std::endl;
			std::cout << "Retry login? y/n\n";
			std::cin >> choice;
			switch (choice)
			{
			case 'y':
			{
				login = false;
				break;
			}
			case 'n':
			{
				login = true;
				break;
			}
			default:
			{
				std::cin >> choice;
				break;
			}
			}
		}

	} while (!login);
	return 0;
}
