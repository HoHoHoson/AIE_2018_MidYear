#include <iostream>
#include <string>
#include "hashMap.h"


int main()
{
	hashMap<1024, std::string, int> map1;

	map1.addValue("Matt", 423);
	map1.addValue("James", 490);
	map1.addValue("Karley", 630);
	map1.display();

	map1.removeValue("James");

	map1["Karley"];
	map1.clearAll();
	map1.display();

	std::cout << "\n";
	system("pause");
	return 0;
}