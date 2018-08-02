#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

//struct Data
//{
//	std::string input;
//};
//
//struct DataConversion
//{
//	DataConversion(){}
//	DataConversion(const Data& test)
//	{
//		assert(test.input.size() < 256);
//
//		strcpy_s(wordArray, 255, test.input.data());
//	}
//	char wordArray[256];
//};
	

int main()
{
	std::string forScience = "potato";

	std::string writeTo;
	//Data test;
	//test.input = "test string";


	std::fstream fout("data.dat", std::ios::out | std::ios::binary);
	if (fout.good())
	{
		//DataConversion d1(test);
		char chips[256];
		strcpy_s(chips, 255, forScience.data());
		fout.write((char*)&chips, sizeof(std::string));
		forScience = "";
		//test.input = "";
	}
	else
		std::cout << "Error\n";
	fout.close();

	std::cout << forScience;

	std::fstream fin("data.dat", std::ios::in | std::ios::binary);
	if (fin.good())
	{
		while (!fin.eof() && fin.peek() != EOF)
		{
			//DataConversion d2;
			char chicken[256];
			fin.read((char*)chicken, sizeof(std::string));
			writeTo = chicken;
			//writeTo = d2.wordArray;
		}
	}
	else 
		std::cout << "Error\n";
	fin.close();

	std::cout << writeTo;
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
