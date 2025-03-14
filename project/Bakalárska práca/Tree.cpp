#include "Tree.h"

Tree::Tree(Data* inputData)
{
	this->data = inputData;
	this->confusionMatrix = new ConfusionMatrix();
	this->stats = new Statistics();
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
	if (this->root == nullptr) {
		this->root = new Node();
		node = this->root;
	}
	if (node == nullptr) {
		node = new Node();
	}
	if (this->data->isLeaf(indexs)) {
		node->setLeaf(true);
		node->setTargetClassValue(this->data->getTargetClassValue(indexs[0]));
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
	if (gainRatio[maxGain][0] < 0.01) {
		node->setLeaf(true);
		node->setMajorityClass(this->data->findMajorityClass(indexs));
		return node;
	}
	node->setLabel(this->data->getAttributeName(maxGain));
	node->setSplitAttribute(maxGain);
	if (std::isnan(gainRatio[maxGain][1])) {
		std::vector<std::string> labels = this->data->getDiferentLabels(maxGain, indexs);
		avalaibleAttributes[maxGain] = false;
		for (int i = 0; i < labels.size(); i++) {
			//node->setTreshold(-1)
			Node* child = this->buildTree(nullptr, this->data->createSubset(indexs, maxGain, labels[i]), avalaibleAttributes);
			child->setNodeValue(labels[i]);
			node->addChild(child);
		}
	}
	else {
		node->setTreshold(gainRatio[maxGain][1]);
		//Node* left = new Node();
		Node* left = this->buildTree(nullptr, this->data->createSubsetForNumbers(indexs, maxGain, gainRatio[maxGain][1], false), avalaibleAttributes);
		node->addChild(left);
		//Node* right = new Node();
		Node * right = this->buildTree(nullptr, this->data->createSubsetForNumbers(indexs, maxGain, gainRatio[maxGain][1], true), avalaibleAttributes);
		node->addChild(right);
	}
	return node;
}

Tree::~Tree()
{
	if (this->root != nullptr) {
		this->cleanTree(this->root);
		this->root = nullptr;
	}
	if (this->confusionMatrix != nullptr) {
		delete confusionMatrix;
		this->confusionMatrix = nullptr;
	}
	if (this->stats != nullptr) {
		delete this->stats;
		this->stats = nullptr;
	}
	this->data = nullptr;

}

void Tree::printTree()
{
	std::cout << "=== DECISION TREE ===" << std::endl;
	this->printSubTree(this->root, 0);
}

void Tree::printSubTree(Node* node, int depth)
{
	if (node == nullptr) return;

	std::string indent(depth * 2, ' ');

	if (node->getLeaf()) {
		if (!node->getTargetClassValue().empty()) {
			std::cout << indent << "-> [Leaf] Class: " << node->getTargetClassValue() << std::endl;
		}
		else {
			std::cout << indent << "-> [Leaf] Majority Class: " << node->getMajorityClass() << std::endl;
		}
		return;
	}

	std::cout << indent << "[Node] Split on attribute: " << node->getLabel();

	if (node->getTreshold() != -1) {
		std::cout << " | Threshold: " << node->getTreshold();
	}

	std::cout << std::endl;

	for (int i = 0; i < node->getNumberOfChildren(); ++i) {
		Node* child = node->getChild(i);
		std::string childIndent((depth + 1) * 2, ' ');

		if (node->getTreshold() == -1) {
			std::cout << childIndent << "=> Value = " << child->getNodeValue() << std::endl;
		}
		else {
			if (i == 0)
				std::cout << childIndent << "=> Value <= " << node->getTreshold() << std::endl;
			else
				std::cout << childIndent << "=> Value > " << node->getTreshold() << std::endl;
		}
		printSubTree(child, depth + 2);
	}
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
	for (int i = 0; i < indexs.size(); i++) {
		std::string predictValue = this->predict(this->data->getSample(indexs[i]));
		std::string realValue = this->data->getTargetClassValue(indexs[i]);
		this->confusionMatrix->addPrediction(realValue, predictValue);
	}
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
	while (node->getNumberOfChildren() > 0) {
		Node* child = node->getChild(node->getNumberOfChildren() - 1);
		this->cleanTree(child); 
		node->removeChild(node->getNumberOfChildren() - 1);
	}
	delete node;
}

std::string Tree::predict(std::vector<std::string> sample)
{
	Node* current = this->root;
	while (!current->getLeaf()) {
		int attrIndex = current->getSplitAttribute();
		std::string value = sample[attrIndex];
		int size = current->getNumberOfChildren();
		if (current->getTreshold() == -1) {
			for (int i = 0; i < size; i++) {
				if (value == current->getChild(i)->getNodeValue()) {
					current = current->getChild(i);
					break;
				}
			}
		}
		else {
			double newValue = std::stod(value);
			if (newValue <= current->getChild(0)->getTreshold()) {
				current = current->getChild(0);
			}
			else {
				current = current->getChild(1);
			}
		}
	}
	if (current->getTargetClassValue() != "") {
		return current->getTargetClassValue();
	}
	return current->getMajorityClass();
}

void Tree::calculateStatistics()
{
	const std::vector<std::vector<int>> matrix = this->confusionMatrix->getMatrix();
	double accurancy = 0.0;
	double precision = 0.0;
	double recall = 0.0;
	double fscore = 0.0;
	if (this->confusionMatrix->sumOfMatrix() != 0) {
		this->stats->addAccuracy((static_cast<double>(matrix[0][0] + matrix[1][1]) / (this->confusionMatrix->sumOfMatrix())));
		if ((matrix[0][0] + matrix[0][1]) != 0) {
			precision = (static_cast<double>(matrix[0][0]) / (matrix[0][0] + matrix[0][1]));
			this->stats->addPrecision((static_cast<double>(matrix[0][0]) / (matrix[0][0] + matrix[0][1])));
		}
		if ((matrix[0][0] + matrix[1][0]) != 0) {
			recall = (static_cast<double>(matrix[0][0]) / (matrix[0][0] + matrix[1][0]));
			this->stats->addRecall((static_cast<double>(matrix[0][0]) / (matrix[0][0] + matrix[1][0])));
		}
		if (recall + precision != 0) {
			this->stats->addFscore(2 * (recall * precision) / (recall + precision));
		}
	}
}

void Tree::prunning(Node* node, std::vector<int> indexs)
{
	if (node->getLeaf()) return;

	int attrIndex = node->getSplitAttribute();

	std::vector<std::vector<int>> childrenIndexs;
	if (node->getTreshold() == -1) {
		for (int i = 0; i < node->getNumberOfChildren(); i++) {
			std::string value = node->getChild(i)->getNodeValue();
			std::vector<int> subset = this->data->createSubset(indexs, attrIndex, value);
			prunning(node->getChild(i), subset);
			childrenIndexs.push_back(subset);
		}
	}
	else {
		double threshold = node->getTreshold();
		std::vector<int> leftSubset = this->data->createSubsetForNumbers(indexs, attrIndex, threshold, false);
		std::vector<int> rightSubset = this->data->createSubsetForNumbers(indexs, attrIndex, threshold, true);
		prunning(node->getChild(0), leftSubset);
		prunning(node->getChild(1), rightSubset);
		childrenIndexs.push_back(leftSubset);
		childrenIndexs.push_back(rightSubset);
	}

	std::string majority = this->data->findMajorityClass(indexs);

	int leafErrors = 0;
	for (int i : indexs) {
		if (this->data->getTargetClassValue(i) != majority) {
			leafErrors++;
		}
	}

	int subtreeErrors = 0;
	for (int i = 0; i < node->getNumberOfChildren(); i++) {
		Node* child = node->getChild(i);
		std::vector<int>& childIndexs = childrenIndexs[i];
		for (int j : childIndexs) {
			std::string predicted = predictFromNode(child, this->data->getSample(j));
			if (predicted != this->data->getTargetClassValue(j)) {
				subtreeErrors++;
			}
		}
	}

	if (leafErrors <= subtreeErrors - 1) {
		node->setLeaf(true);
		node->setMajorityClass(majority);
		while (node->getNumberOfChildren() > 0) {
			cleanTree(node->getChild(0));
			node->removeChild(0);
		}
	}
}

std::string Tree::predictFromNode(Node* node, std::vector<std::string> sample)
{
	Node* current = node;
	while (!current->getLeaf()) {
		int attrIndex = current->getSplitAttribute();
		std::string value = sample[attrIndex];
		if (current->getTreshold() == -1) {
			bool found = false;
			for (int i = 0; i < current->getNumberOfChildren(); i++) {
				if (value == current->getChild(i)->getNodeValue()) {
					current = current->getChild(i);
					found = true;
					break;
				}
			}
			if (!found) break; // fallback
		}
		else {
			double val = std::stod(value);
			if (val <= current->getChild(0)->getTreshold()) {
				current = current->getChild(0);
			}
			else {
				current = current->getChild(1);
			}
		}
	}
	if (current->getTargetClassValue() != "") {
		return current->getTargetClassValue();
	}
	return current->getMajorityClass();
}

void Tree::pesimisticPruning(Node* node, std::vector<int> indexs)
{
	if (node->getLeaf()) return;

	int attrIndex = node->getSplitAttribute();

	std::vector<std::vector<int>> childrenIndexs;
	if (node->getTreshold() == -1) {
		for (int i = 0; i < node->getNumberOfChildren(); i++) {
			std::string value = node->getChild(i)->getNodeValue();
			std::vector<int> subset = this->data->createSubset(indexs, attrIndex, value);
			pesimisticPruning(node->getChild(i), subset);
			childrenIndexs.push_back(subset);
		}
	}
	else {
		double threshold = node->getTreshold();
		std::vector<int> leftSubset = this->data->createSubsetForNumbers(indexs, attrIndex, threshold, false);
		std::vector<int> rightSubset = this->data->createSubsetForNumbers(indexs, attrIndex, threshold, true);
		pesimisticPruning(node->getChild(0), leftSubset);
		pesimisticPruning(node->getChild(1), rightSubset);
		childrenIndexs.push_back(leftSubset);
		childrenIndexs.push_back(rightSubset);
	}

	std::string majority = this->data->findMajorityClass(indexs);

	int leafErrors = 0;
	for (int i : indexs) {
		if (this->data->getTargetClassValue(i) != majority) {
			leafErrors++;
		}
	}
	double leafErrorEstimate = (leafErrors + 0.5) / (double)indexs.size();

	int subtreeErrors = 0;
	int subtreeSize = 0;
	for (int i = 0; i < node->getNumberOfChildren(); i++) {
		Node* child = node->getChild(i);
		std::vector<int>& childIndexs = childrenIndexs[i];
		for (int j : childIndexs) {
			std::string predicted = predictFromNode(child, this->data->getSample(j));
			if (predicted != this->data->getTargetClassValue(j)) {
				subtreeErrors++;
			}
		}
		subtreeSize += childIndexs.size();
	}
	double subtreeErrorEstimate = (subtreeErrors + 0.5 * node->getNumberOfChildren()) / (double)indexs.size();

	if (leafErrorEstimate <= subtreeErrorEstimate) {
		node->setLeaf(true);
		node->setMajorityClass(majority);
		while (node->getNumberOfChildren() > 0) {
			cleanTree(node->getChild(0));
			node->removeChild(0);
		}
	}
}


void Tree::crossValidation(std::vector<int>& indexs, std::vector<bool> availableAttributes)
{
	int numberOfInterval = 2;
	int foldSize = this->data->getSize() / numberOfInterval;

	for (int i = 0; i < numberOfInterval; i++) {
		std::vector<int> trainIndexs, testIndexs;

		for (int j = 0; j < this->data->getSize(); j++) {
			if (j >= i * foldSize && j < (i + 1) * foldSize) {
				testIndexs.push_back(indexs[j]); // testovacie dáta
			}
			else {
				trainIndexs.push_back(indexs[j]); // tréningové dáta
			}
		}

		// 1. Vybuduj strom na tréningových dátach
		this->buildTree(this->root, trainIndexs, availableAttributes);

		// 2. Pruning na tréningových dátach (alebo bez pruning, ak chceš raw strom)
		this->pesimisticPruning(this->root, trainIndexs);
		// this->prunning(this->root, trainIndexs); // ak chceš REP

		// 3. Výpis stromu (voliteľné)
		this->printTree();

		// 4. Testuj na testovacích dátach
		this->testModel(testIndexs);

		// 5. Vyhodnoť metriky
		this->calculateStatistics();

		// 6. Vyčisti strom pre ďalší fold
		this->cleanTree(this->root);
		this->root = nullptr;
	}

	// Výpis priemerných metrík
	std::cout << "Accurancy : " << this->stats->getAverageAccuracy() << std::endl;
	std::cout << "Precision :" << this->stats->getAveragePrecision() << std::endl;
	std::cout << "Recall :" << this->stats->getAverageRecall() << std::endl;
	std::cout << "F-score :" << this->stats->getAverageFscore() << std::endl;
}

