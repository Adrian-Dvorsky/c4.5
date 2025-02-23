#include "Tree.h"

Tree::Tree(Data* inputData)
{
	this->root = new Node();
	this->data = inputData;
}



Node* Tree::buildTree(Node* node, std::vector<int> indexs)
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
	int maxGain = this->findMax(gainRation, node);
	std::vector<std::string> labels = this->data->getDiferentLabels(maxGain, indexs);
	for (int i = 0; i < labels.size(); i++) {
		Node* node = new Node();
		node->setLabel(this->data->getAttributeName(maxGain));
		node->setSplitAttribute(maxGain);
		node->addChild(this->buildTree(node, this->data->createSubset(indexs, i, labels[i])));
	}
	return node;
}

void Tree::printTree()
{

}

int Tree::findMax(std::vector<double>& vec, Node * node)
{
	int index = -1;
	double max = -1.0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > max && node->getSplitAttribute() != i ) {
			max = vec[i];
			index = i;
		}
	}
	return index;
}
