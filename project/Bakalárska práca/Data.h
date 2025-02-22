#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Data
{
private:
	std::vector<std::vector<std::string>> data;
	std::vector<std::string> atributesName;
	int targetClass;
	double targetClassEtropyInfo;
public:
	Data() : targetClass(-1) {};
	int getSize() { return this->data.size(); };
	int getNumberOfAttributes() { return this->data[0].size(); };
	void LoadData(std::string name);
	int numberOfLaabels(int index, std::vector<int>& indexs);
	std::vector<std::string> getDiferentLabels(int index, std::vector<int>& indexs);
	int numberOfPresence(int index, std::string value, std::vector<int>& indexs);
	void setTargetClass(int number) {
		this->targetClass = number;
	};
	~Data();
	std::vector<int> createSubset(std::vector<int> indexs, int atttributeIndex, std::string value);
	bool isLeaf(std::vector<int>& indexs);
	double getTargetClassEtropyInfo() { return this->targetClassEtropyInfo;};
	double calculateEntropyInfo(int index, std::vector<int>& indexs);
	std::unordered_map<std::string, std::vector<int>> getLabels(int index, std::vector<int>& indexs);
private:
	double calculateEntropy();
};

