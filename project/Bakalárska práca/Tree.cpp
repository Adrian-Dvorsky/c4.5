#include "Tree.h"

Tree::Tree(Data* inputData)
{
	this->root = new Node();
	this->data = inputData;
}

void Tree::startBuilding()
{
	std::vector<int> numbers;
	for (int i = 0; i < this->data->getSize(); i++) {
		numbers.push_back(i);
	}
	std::vector<bool> availableAttributes;
	for (int i = 0; i < this->data->getNumberOfAttributes() - 1; i++)
	{
		availableAttributes.push_back(true);
	}
	this->crossValidation(numbers, availableAttributes);
}



Node* Tree::buildTree(Node* node, std::vector<int> indexs, std::vector<bool> avalaibleAttributes)
{
	if (this->data->isLeaf(indexs)) {
		node->setLeaf(true);
		return node;
	}
	if (this->isHomogene(indexs)) {
		node->setLeaf(true);
		node->setMajorityClass(this->data->findMajorityClass(indexs));
		return node;
	}
	std::vector<std::vector<double>> gainRatio;
	for (int i = 0; i < this->data->getNumberOfAttributes() - 1; i++) {
		gainRatio.push_back(this->data->getGainTest(i, indexs));
	}
	if (this->useAllAtributes(gainRatio)) {
		node->setLeaf(true);
		node->setMajorityClass(this->data->findMajorityClass(indexs));
		return node;
	}
	int maxGain = this->findMax(gainRatio, avalaibleAttributes);
	if (std::isnan(gainRatio[maxGain][1])) {
		std::vector<std::string> labels = this->data->getDiferentLabels(maxGain, indexs);
		avalaibleAttributes[maxGain] = false;
		for (int i = 0; i < labels.size(); i++) {
			Node* node = new Node();
			node->setLabel(this->data->getAttributeName(maxGain));
			node->setSplitAttribute(maxGain);
			node->addChild(this->buildTree(node, this->data->createSubset(indexs, maxGain, labels[i]), avalaibleAttributes));
		}
	}
	else {
		Node* node = new Node();
		node->setLabel(this->data->getAttributeName(maxGain));
		node->setSplitAttribute(maxGain);
		node->setTreshold(gainRatio[maxGain][1]);
		node->addChild(this->buildTree(node, this->data->createSubsetForNumbers(indexs, maxGain, gainRatio[maxGain][1], false), avalaibleAttributes));
		Node* node2 = new Node();
		node2->setLabel(this->data->getAttributeName(maxGain));
		node2->setSplitAttribute(maxGain);
		node2->setTreshold(gainRatio[maxGain][1]);
		node2->addChild(this->buildTree(node2, this->data->createSubsetForNumbers(indexs, maxGain, gainRatio[maxGain][1], true), avalaibleAttributes));
	}
	return node;
}

Tree::~Tree()
{
	this->cleanTree(this->root);
}

void Tree::printTree()
{

}

int Tree::findMax(std::vector<std::vector<double>> vec, std::vector<bool> avalaibleAttributes)
{
	double max = -1.0;
	int index = -1.0; 
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i][0] > max && avalaibleAttributes[i]) {
			max = vec[i][0];
			index = i;
		}
	}
	return index;
}

void Tree::testModel(std::vector<int>& indexs)
{
}

bool Tree::isHomogene(std::vector<int>& indexs)
{
	for (int i = 0; i < this->data->getNumberOfAttributes() - 1; i++) {
		if (!this->data->isHomogene(i, indexs)) {
			return false;
		}
	}
	return true;

}

bool Tree::useAllAtributes(std::vector<std::vector<double>> gainRatio)
{
	for (int i = 0; i < gainRatio.size(); i++) {
		if (gainRatio[i][0] > 0) {
			return false;
		}
	}
	return true;
}

void Tree::cleanTree(Node* node)
{
	if (node == nullptr) {
		return;
	}
	int size = node->getNumberOfChildren();
	if (size == 0) {
		delete node;
	}
	else {
		for (int i = 0; i < size; i++) {
			this->cleanTree(node->getChild(i));
		}
		node->clearChildren();
	}
	delete node;
}


void Tree::crossValidation(std::vector<int>& indexs, std::vector<bool> avalaibleAttributes)
{
	int foldSize = this->data->getSize() / 4;
	for (int i = 0; i < 4; i++) {
		std::vector<int> trainIndexs, testIndexs;
		for (int j = 0; j < this->data->getSize(); i++) {
			if (j >= i * foldSize && j < (i + 1) * foldSize) {
				testIndexs.push_back(indexs[j]);
			} else {
				trainIndexs.push_back(indexs[j]);
			}
		}
		this->buildTree(this->root, trainIndexs, avalaibleAttributes);


	}
}

