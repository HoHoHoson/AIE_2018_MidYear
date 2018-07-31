#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string input = "test string";
	std::string write;
	char testString[] = "test";
	char* readString;


	std::fstream fout("data.dat", std::ios::out | std::ios::binary);
	if (fout.good())
	{
		fout.write((char*)&input, sizeof(input) / sizeof(std::string));
	}
	else
		std::cout << "Error\n";
	fout.close();


	std::fstream fin("data.dat", std::ios::in | std::ios::binary);
	std::streampos size;
		size = fin.tellg();
		readString = new char[size];
	if (fin.good())
	{
		while (!fin.eof() && fin.peek() != EOF)
		{
			fin.read(readString, size);
		}
	}
	else 
		std::cout << "Error\n";
	fin.close();

	std::cout << readString;
	std::cout << "\n";
	

	//Text File Stuff

	//std::ofstream myFile;
	//myFile.open("test.txt", std::ios_base::out|std::ios_base::_Nocreate);

	//if (myFile.is_open())
	//{
	//	myFile << "Test" << std::endl;
	//}
	//else
	//	std::cout << "File not found\n";

	//myFile.close();

	system("pause");
	return 0;
}