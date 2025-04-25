#pragma once
#include "Node.h"
#include "Data.h"
#include <vector>
#include <string>
#include "ConfusionMatrix.h"
#include "Statistics.h"
class Tree
{
private:
	Node* root = nullptr;
	Data* data = nullptr;
	ConfusionMatrix* confusionMatrix = nullptr;
	Statistics* stats;
public:
	Node* getRoot() { return this->root; };
	Tree(Data* inputData);
	void startBuilding();
	Node* buildTree(Node* node, std::vector<int> indexs, std::vector<bool> avalaibleAttributes);

	~Tree();
	void printTree();
	void printSubTree(Node* node, int depth);
	void testModel(std::vector<int>& indexs);
private:
	int findMax(std::vector<std::vector<double>> vec, std::vector<bool> avalaibleAttributes);
	void crossValidation(std::vector<int>& indexs, std::vector<bool> avalaibleAttributes);
	bool isHomogene(std::vector<int>& indexs);
	bool useAllAtributes(std::vector<std::vector<double>> gainRatio);
	void cleanTree(Node * node);
	std::string predict(std::vector<std::string> sample);
	void calculateStatistics();
	void prunning(Node* node, std::vector<int> indexs);
	std::string predictFromNode(Node* node, std::vector<std::string> sample);
	void pesimisticPruning(Node* node, std::vector<int> indexs);
	void saveResult();
	void calculateImportance(Node * node, std::vector<double>& importance);
	void printImportance();
};

