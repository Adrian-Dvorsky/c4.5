#include "Tree.h"

Tree::Tree(Data* inputData)
{
	this->root = new Node();
	this->data = inputData;
}



Node* Tree::buildTree(Node* node, std::vector<int> indexs)
{
	if (this->data->isLeaf(indexs)) {
		Node* node = new Node();
		node->setLeaf(true);
		return node;
	}
	std::vector<int> numbers;
	for (int i = 0; i < this->data->getSize(); i++) {
		numbers.push_back(i);
	}
	std::vector<double> test;
	for (int i = 0; i < this->data->getNumberOfAttributes() - 1; i++) {
		test.push_back(this->data->calculateEntropyInfo(i, numbers));
	}
	return nullptr;
}

void Tree::printTree()
{
}
