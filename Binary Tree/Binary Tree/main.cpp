#include "BinaryTree.h"
#include <time.h>
#include <random>

int main()
{
	srand((unsigned int)time(nullptr));

	BinaryTree<int>* bTree = new BinaryTree<int>;

	bTree->addNode(10);
	bTree->addNode(11);
	bTree->addNode(2);
	bTree->addNode(1);
	bTree->addNode(15);
	bTree->addNode(19);
	bTree->addNode(20);
	bTree->addNode(9);
	bTree->addNode(14);

	bTree->drawTree();


	std::cout << "\n";
	system("pause");
	return 0;
}