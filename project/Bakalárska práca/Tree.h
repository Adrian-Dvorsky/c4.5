#pragma once
#include "Node.h"
#include "Data.h"
#include <vector>
#include <string>
class Tree
{
private:
	Node* root;
	Data* data = nullptr;
public:
	Node* getRoot() { return this->root; };
	Tree(Data* inputData);
	Node* buildTree(Node* node, std::vector<int> indexs);
	void printTree();
private:
	int findMax(std::vector<double>& vec, Node* node);
};

