#include "Tree.h"

Tree::Tree(Data* inputData)
{
	this->root = new Node();
	this->data = inputData;
}



Node* Tree::buildTree(Node* node, std::vector<int> indexs, std::vector<bool> avalaibleAttributes)
{
	if (this->data->isLeaf(indexs)) {
		node->setLeaf(true);
		return node;
	} 
	double targetClassEntropy = this->data->getEntropyInfoTargetClass(indexs);
	std::vector<double> entropyInfo;
	for (int i = 0; i < this->data->getNumberOfAttributes() - 1; i++) {
		entropyInfo.push_back(this->data->calculateEntropyInfo(i, indexs));
	}
	std::vector<double> informationGain;
	for (int i = 0; i < entropyInfo.size(); i++) {
		informationGain.push_back(targetClassEntropy - entropyInfo[i]);
	}
	std::vector<double> splitInfo;
	for (int i = 0; i < entropyInfo.size(); i++) {
		splitInfo.push_back(this->data->calculateSplitInfo(i, indexs));
	}
	std::vector<double> gainRation;
	for (int i = 0; i < informationGain.size(); i++) {
		gainRation.push_back(informationGain[i] / splitInfo[i]);
	}
	int maxGain = this->findMax(gainRation, avalaibleAttributes, indexs);
	if (maxGain == -1) {
		std::vector<std::string> labels = this->data->getDiferentLabels(this->data->getNumberOfAttributes() - 1, indexs);
		for (int i = 0; i < labels.size(); i++) {
			Node* node = new Node();
			node->setLabel(this->data->getAttributeName(this->data->getNumberOfAttributes() - 1));
			node->setSplitAttribute(this->data->getNumberOfAttributes() - 1);
			node->addChild(this->buildTree(node, this->data->createSubset(indexs, i, labels[i]), avalaibleAttributes));
		}
	}
	else {
		std::vector<std::string> labels = this->data->getDiferentLabels(maxGain, indexs);
		avalaibleAttributes[maxGain] = false;
		for (int i = 0; i < labels.size(); i++) {
			Node* node = new Node();
			node->setLabel(this->data->getAttributeName(maxGain));
			node->setSplitAttribute(maxGain);
			node->addChild(this->buildTree(node, this->data->createSubset(indexs, maxGain, labels[i]), avalaibleAttributes));
		}
	}
	return node;
}

void Tree::printTree()
{

}

int Tree::findMax(std::vector<double>& vec, std::vector<bool> avalaibleAttributes, std::vector<int> indexs)
{
	int index = -1;
	double max = -1.0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > max && avalaibleAttributes[i] && !this->data->isHomogene(i, indexs)) {
			max = vec[i];
			index = i;
		}
	}
	return index;
}
