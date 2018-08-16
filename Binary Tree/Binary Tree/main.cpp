#include "BinaryTree.h"
#include <time.h>
#include <random>

int main()
{
	srand((unsigned int)time(nullptr));

	BinaryTree<int>* bTree = new BinaryTree<int>;

	bTree->addNode(10);
	for (int i = 0; i < 25; ++i)
		bTree->addNode(rand() % 21);

	bTree->drawTree();


	std::cout << "\n";
	system("pause");
	return 0;
}