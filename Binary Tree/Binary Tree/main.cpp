#include "BinaryTree.h"
#include <time.h>
#include <random>

int main()
{
	srand((unsigned int)time(nullptr));

	BinaryTree<int>* bTree = new BinaryTree<int>;

	std::cout << "\n[Added a set of numbers to the Binary Tree]\n";
	bTree->addNode(10);
	bTree->addNode(5);
	bTree->addNode(15);
	bTree->addNode(4);
	bTree->addNode(6);
	bTree->addNode(14);
	bTree->addNode(16);
	bTree->addNode(17);
	bTree->drawTree();

	std::cout << "\n[Removed a leaf node '4']\n";
	bTree->removeNode(4);
	bTree->drawTree();

	std::cout << "\n[Removed a node with one child '16']\n";
	bTree->removeNode(16);
	bTree->drawTree();

	std::cout << "\nRemoved a node with two children '10'\n";
	bTree->removeNode(10);
	bTree->drawTree();

	std::cout << "\nCleared the Binary Tree\n";
	bTree->clear();
	bTree->drawTree();


	std::cout << "\n\n";
	system("pause");
	return 0;
}