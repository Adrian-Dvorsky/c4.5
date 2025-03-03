#include "Data.h"
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cctype>
#include <regex>

void Data::LoadData(std::string name)
{
	std::ifstream file(name);
	if (!file.is_open()) {
		std::cout << "Chyba\n" << std::endl;
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string value; 
	while (std::getline(ss, value, ',')) {
		this->atributesName.push_back(value);
	}
	std::getline(file, line);
	std::stringstream sss(line);
	while (std::getline(sss, value, ',')) {
		this->atributeType.push_back(value);
	}
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string value;
		std::vector<std::string> rowData;
		while (std::getline(ss, value, ',')) {
			rowData.push_back(value);
		}
		this->data.push_back(rowData);
	}
}

int Data::numberOfPresence(int index, std::string value, std::vector<int>& indexs)
{
	int number = 0;
	for (int i = 0; i < indexs.size(); i++) {
		if (value == this->data[indexs[i]][index]) {
			number++;
		}
	}
	return number;
}

int Data::numberOfLaabels(int index, std::vector<int>& indexs)
{
	std::unordered_set<std::string> unique;
	for (int i = 1; i < indexs.size(); i++) {
		unique.insert(this->data[index][indexs[i]]);
	}
	return unique.size();
}

std::vector<std::string> Data::getDiferentLabels(int index, std::vector<int>& indexs)
{
	std::unordered_set<std::string> unique;
	for (int i = 0; i < indexs.size(); i++) {
		unique.insert(this->data[indexs[i]][index]);
	}

	std::vector<std::string> labels(unique.begin(), unique.end());
	return labels;
}

Data::~Data()
{

}

std::vector<int> Data::createSubset(std::vector<int>& indexs, int atttributeIndex, std::string value)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		std::string test = this->data[indexs[i]][atttributeIndex];
		if (this->data[indexs[i]][atttributeIndex] == value) {
			newIndexs.push_back(indexs[i]);
		}
	}
	return newIndexs;
}

bool Data::isLeaf(std::vector<int>& indexs)
{
	std::string value = this->data[this->targetClass][indexs[0]];
	for (int i = 1; i < indexs.size(); i++) {
		if (this->data[this->targetClass][indexs[i]] != value) {
			return false;
		}
	}
	return true;
}

double Data::calculateEntropyInfo(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(index, indexs);
	double entropy = 0.0;
	for (auto& partHast : hashMap) {
		std::vector<std::string> labels = this->getDiferentLabels(this->targetClass, indexs);
		std::vector<int> numberOfPresence;
		double partialEntropy = 0.0;
		for (int i = 0; i < labels.size(); i++) {
			numberOfPresence.push_back(this->numberOfPresence(this->targetClass, labels[i], partHast.second));
		}
		for (int i = 0; i < numberOfPresence.size(); i++) {
			if (numberOfPresence[i] != 0) {
				double p = (double)numberOfPresence[i] / (this->data.size());
				partialEntropy += -p * log2(p);
			}
		}
		entropy += ((double) partHast.second.size() / indexs.size()) * partialEntropy;
	}
	return entropy;
}

std::unordered_map<std::string, std::vector<int>> Data::getLabels(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap;
	for (int i = 0; i < indexs.size(); i++) {
		hashMap[this->data[indexs[i]][index]].push_back(indexs[i]);
	}
	return hashMap;
}

double Data::calculateSplitInfo(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(index, indexs);
	double splitInfo = 0.0;
	for (auto& value : hashMap) {
		double p = (double) value.second.size()/ (this->data.size());
		splitInfo += -p * log2(p);
	}
	return splitInfo;
}

double Data::getEntropyInfoTargetClass(std::vector<int> indexs)
{
	double entropy = 0.0;
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(this->targetClass, indexs);
	for (auto& value : hashMap) {
		double p = (double)value.second.size() / (this->data.size());
		entropy += -p * log2(p);
	}
	return entropy;
}

bool Data::isHomogene(int index, std::vector<int>& indexs)
{
	std::string value = this->data[indexs[0]][index];
	for (int i = 0; i < indexs.size(); i++) {
		if (value != this->data[indexs[i]][index]) {
			return false;
		}
	}
	return true;
}

double Data::getGainTest(int index, std::vector<int>& indexs)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<double> entropyInfo;
	for (int i = 0; i < this->getNumberOfAttributes(); i++) {
		if (this->atributeType[index] == "i") {
			this->findTreshold(index, indexs);
		}
	}
	return 0;
}


double Data::findTreshold(int index, std::vector<int>& indexs)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<int> newData;
	for (int i = 0; i < indexs.size(); i++) {
		newData.push_back(std::stoi(this->data[indexs[i]][index]));
	}
	std::sort(newData.begin(), newData.end());
	std::vector<int> tresholds;
	for (int i = 0; i < indexs.size() -1; i++) {
		if (newData[i] != newData[i + 1]) {
			tresholds.push_back((newData[i] + newData[i + 1]) / 2);
		}
	}
	int bestTreshold;
	double bestGainRatio;
	for (int i = 0; i < tresholds.size(); i++) {
		std::vector<std::string> labels = this->getDiferentLabels(this->targetClass, indexs);
		std::vector<int> leftInterval = this->createIndexsForTreshold(index, indexs, false, tresholds[i]);
		std::vector<int> rightInterval = this->createIndexsForTreshold(index, indexs, true, tresholds[i]);
		double entropy = -1.0;
		double partialEntropy = -1.0;
		std::vector<int> numberOfPresenceLeft;
		std::vector<int> numberOfPresenceRight;
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceLeft.push_back(this->numberOfPresence(this->targetClass, labels[i], leftInterval));
		}
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceRight.push_back(this->numberOfPresence(this->targetClass, labels[i], rightInterval));
		}
		for (int i = 0; i < numberOfPresenceLeft.size(); i++) {
			if (numberOfPresenceLeft[i] != 0) {
				double p = (double)numberOfPresenceLeft[i] / (numberOfPresenceLeft.size());
				partialEntropy += -p * log2(p);
			}
		}
		entropy += ((double)numberOfPresenceLeft.size() / indexs.size()) * partialEntropy;
		for (int i = 0; i < numberOfPresenceRight.size(); i++) {
			if (numberOfPresenceRight[i] != 0) {
				double p = (double)numberOfPresenceRight[i] / (numberOfPresenceRight.size());
				partialEntropy += -p * log2(p);
			}
		}
		entropy += ((double)numberOfPresenceRight.size() / indexs.size()) * partialEntropy;
		double gain = targetClassEntropy - entropy;
		double splitInfo = 0.0;
		double p = ((double)leftInterval.size() / indexs.size());
		splitInfo += -p * log2(p);
		double p = ((double)rightInterval.size() / indexs.size());
		splitInfo += -p * log2(p);
		double gainRatio = gain / splitInfo;
		if (bestGainRatio > gainRatio) {
			bestGainRatio = gainRatio;
			bestTreshold = tresholds[i];
		}
	}
	return bestTreshold;

}

std::vector<int> Data::createIndexsForTreshold(int index, std::vector<int>& indexs, bool isHigher, double treshold)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		double value = std::stod(this->data[indexs[i]][index]);
		if (isHigher) {
			if (value > treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
		else {
			if (value <= treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
	}
	return newIndexs;
}




