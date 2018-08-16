#include <iostream>
#include <string>
#include "hashMap.h"


int main()
{
	hashMap<1024, std::string, int> map1;

	map1.addValue("Matt", 423);
	map1.addValue("James", 490);
	map1.addValue("Karley", 630);


	return 0;
}