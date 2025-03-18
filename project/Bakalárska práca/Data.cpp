#include "Data.h"
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cctype>
#include <regex>

bool Data::LoadData(std::string& name)
{
	std::ifstream file(name);
	if (!file.is_open()) {
		return false;
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
	file.close();
	return true;
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

std::vector<int> Data::createSubsetForNumbers(std::vector<int>& indexs, int atttributeIndex, double treshold, bool isHigher)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		double value = std::stod(this->data[indexs[i]][atttributeIndex]);
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

bool Data::isLeaf(std::vector<int>& indexs)
{
	if (indexs.size() == 1) {
		return true;
	}
	std::string value = this->data[indexs[0]][this->targetClass];
	for (int i = 1; i < indexs.size(); i++) {
		if (this->data[indexs[i]][this->targetClass] != value) {
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
				double p = (double)numberOfPresence[i] / (partHast.second.size());
				partialEntropy += -p * log2(p);
			}
		}
		entropy += ((double)partHast.second.size() / indexs.size()) * partialEntropy;
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
		double p = (double) value.second.size()/ (indexs.size());
		splitInfo += -p * log2(p);
	}
	return splitInfo;
}

double Data::getEntropyInfoTargetClass(std::vector<int> indexs)
{
	double entropy = 0.0;
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(this->targetClass, indexs);
	for (auto& value : hashMap) {
		double p = (double)value.second.size() / (indexs.size());
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

std::vector<double> Data::getGainTest(int index, std::vector<int>& indexs)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<double> gainRatio;
	if (this->atributeType[index] == "i") {
		return this->findTreshold(index, indexs, true);
	}
	else if (this->atributeType[index] == "d") {
		return this->findTreshold(index, indexs, false);
	}
	else {
		double informationGain = targetClassEntropy - this->calculateEntropyInfo(index, indexs);
		if (informationGain < 0.0000001) {
			informationGain = 0;
		}
		double splitInfo = this->calculateSplitInfo(index, indexs);
		double gainRatio = 0.0;
		if (splitInfo == 0) {
			gainRatio = 0;
		}
		else {
			gainRatio = informationGain / splitInfo;
		}
		std::vector<double> retVector;
		retVector.push_back(gainRatio);
		retVector.push_back(std::numeric_limits<double>::quiet_NaN());
		return retVector;
	}
}


std::vector<double> Data::findTreshold(int index, std::vector<int>& indexs, bool isIntiger)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<double> newData;
	for (int i = 0; i < indexs.size(); i++) {
		newData.push_back(std::stod(this->data[indexs[i]][index]));
	}
	std::sort(newData.begin(), newData.end());
	std::vector<double> tresholds;
	for (int i = 0; i < indexs.size() -1; i++) {
		if (newData[i] != newData[i + 1]) {
			if (isIntiger) {
				tresholds.push_back(std::round((newData[i] + newData[i + 1]) / 2));
			}
			else {
				tresholds.push_back((newData[i] + newData[i + 1]) / 2);
			}
		}
	}
	double bestTreshold = -1;
	double bestGainRatio = -1;
	for (int i = 0; i < tresholds.size(); i++) {
		std::vector<std::string> labels = this->getDiferentLabels(this->targetClass, indexs);
		std::vector<int> leftInterval = this->createIndexsForTreshold(index, indexs, false, tresholds[i]);
		std::vector<int> rightInterval = this->createIndexsForTreshold(index, indexs, true, tresholds[i]);
		double entropy = 0.0;
		double partialEntropy = 0.0;
		std::vector<int> numberOfPresenceLeft;
		std::vector<int> numberOfPresenceRight;
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceLeft.push_back(this->numberOfPresence(this->targetClass, labels[j], leftInterval));
		}
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceRight.push_back(this->numberOfPresence(this->targetClass, labels[j], rightInterval));
		}
		for (int j = 0; j < numberOfPresenceLeft.size(); j++) {
			if (numberOfPresenceLeft[j] != 0) {
				double p = (double)numberOfPresenceLeft[j] / (std::accumulate(numberOfPresenceLeft.begin(), numberOfPresenceLeft.end(), 0));
				if (p > 0) {
					partialEntropy += -p * log2(p);
				}
			}
		}
		entropy += ((double)std::accumulate(numberOfPresenceLeft.begin(), numberOfPresenceLeft.end(), 0) / indexs.size()) * partialEntropy;
		partialEntropy = 0;
		for (int j = 0; j < numberOfPresenceRight.size(); j++) {
			if (numberOfPresenceRight[j] != 0) {
				double p = (double)numberOfPresenceRight[j] / (std::accumulate(numberOfPresenceRight.begin(), numberOfPresenceRight.end(), 0));
				if (p > 0) {
					partialEntropy += -p * log2(p);
				}
			}
		}
		entropy += ((double)std::accumulate(numberOfPresenceRight.begin(), numberOfPresenceRight.end(), 0) / indexs.size()) * partialEntropy;
		double gain = targetClassEntropy - entropy;
		if (gain < 0.0000001) {
			gain = 0;
		}
		double splitInfo = 0.0;
		double p = ((double)leftInterval.size() / indexs.size());
		if (p > 0) {
			splitInfo += -p * log2(p);
		}
		if (p > 0) {
			p = ((double)rightInterval.size() / indexs.size());
		}
		splitInfo += -p * log2(p);
		double gainRatio = 0.0;
		if (splitInfo != 0) {
			gainRatio = gain / splitInfo;
		}
		if (gainRatio > bestGainRatio) {
			bestGainRatio = gainRatio;
			bestTreshold = tresholds[i];
		}
		/*
		std::cout<< i<< std::endl;
		std::cout<< tresholds[i] <<std::endl;
		std::cout<< entropy <<std::endl;
		std::cout<< gain <<std::endl;
		std::cout<< splitInfo<<std::endl;
		std::cout<< gainRatio <<std::endl;
		*/
	}
	std::vector<double> returnVector;
	if (bestGainRatio == -1) {
		returnVector.push_back(0);
	}
	else {
		returnVector.push_back(bestGainRatio);
	}
	returnVector.push_back(bestTreshold);
	return returnVector;

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

std::string Data::findMajorityClass(std::vector<int>& indexs)
{

	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(this->targetClass, indexs);
	std::string value;
	int max = -1;
	for (auto& partHash : hashMap) {
		int test = partHash.second.size();
		if (test > max) {
			max = partHash.second.size();
			value = partHash.first;
		}
	}
	return value;
}





