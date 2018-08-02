// BinarySaving.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <cassert>

//Data that you want to save.
struct HighScoreData
{
	std::string playerName; //But you can't due to pointers inside the string variable.
	int playerScore;
};


//This struct is for converting the data into something you can save into binary.
struct HighScoreDataConversion
{
	HighScoreDataConversion() {}
	HighScoreDataConversion(const HighScoreData& value)
	{
		assert(value.playerName.size() < 256); //Assert to make sure that we can fit the data into the temporary converted array.

		strcpy_s(name, 255, value.playerName.data());	//"strcpy_s" Copies and converts the "PlayerName" string into the "name" char array.
		playerScore = value.playerScore;			   //Copies PlayerScore over.
	}

	char name[256];
	int playerScore;
};

int examplemain()
{
	//Data we want copied over.
	HighScoreData scores[] = 
	{
	{ "Bob", 10 },
	{ "Jane", 20 },
	{ "Fred", 30 }
	};

	std::ofstream saveFile;
	saveFile.open("highscores.dat", std::ios::binary | std::ios::out);
	if (saveFile.good())
	{
		for (int i = 0; i < 3; ++i)
		{
			HighScoreDataConversion saveData(scores[i]);	//Converts and stores the data into the temporary variable "saveData"

			/*"sizeof" must equal to the amount of data being saved.
			we are saving "HighScoreDataConversion" structs, therefore
			"sizeof(HighScoreDataConversion)" */
			saveFile.write((char*)&saveData, sizeof(HighScoreDataConversion));	

			//Removing the original data after saving it.
			scores[i].playerName = "";
			scores[i].playerScore = 0;
		}

	}
	saveFile.close();

	std::ifstream loadFile;
	loadFile.open("highscores.dat", std::ios::binary | std::ios::in);
	if (loadFile.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			HighScoreDataConversion saveData;
			loadFile.read((char*)&saveData, sizeof(HighScoreDataConversion));

			scores[i].playerName = saveData.name;
			scores[i].playerScore = saveData.playerScore;
		}

	}
	loadFile.close();

	

	return 0;
}