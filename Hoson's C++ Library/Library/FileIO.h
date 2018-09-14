#pragma once

#include <fstream>

namespace HLib
{
	template<typename T>
	static void saveFile(const char* fileName, const T& writeFrom, unsigned int valueCount = 1)
	{
		std::fstream file;
		file.open(fileName, std::ios::binary | std::ios::out);

		if (file.good() == true)
		{
			T dataBuffer = writeFrom;

			file.write((char*)&dataBuffer, sizeof(T) * valueCount);
		}

		file.close();
	}
	
	template<typename T>
	static void loadFile(const char* fileName, T& readTo, unsigned int valueCount = 1)
	{
		std::fstream file;
		file.open(fileName, std::ios::binary | std::ios::in);

		if (file.good() == true)
		{
			T dataBuffer;

			file.read((char*)&dataBuffer, sizeof(T) * valueCount);
			readTo = dataBuffer;
		}

		file.close();
	}
}