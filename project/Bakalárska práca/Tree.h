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
	Tree(Data* inputData);
	Node* buildTree(Node* node, std::vector<int> indexs);
	void printTree();
};

