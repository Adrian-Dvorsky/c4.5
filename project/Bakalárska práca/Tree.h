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
	void startBuilding();
	Node* buildTree(Node* node, std::vector<int> indexs, std::vector<bool> avalaibleAttributes);

	~Tree();
	void printTree();
private:
	int findMax(std::vector<std::vector<double>> vec, std::vector<bool> avalaibleAttributes);
	void crossValidation(std::vector<int>& indexs, std::vector<bool> avalaibleAttributes);
	void testModel(std::vector<int>& indexs);
	bool isHomogene(std::vector<int>& indexs);
	bool useAllAtributes(std::vector<std::vector<double>> gainRatio);
	void cleanTree(Node * node);
};

