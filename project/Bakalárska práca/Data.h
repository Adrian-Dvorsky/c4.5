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
	std::vector<bool> isContinues;
	int targetClass;
	double targetClassEtropyInfo;
public:
	Data() : targetClass(-1) {};
	~Data();

	int getSize() { return this->data.size(); };
	int getNumberOfAttributes() { return this->data[0].size(); };
	double getTargetClassEtropyInfo() { return this->targetClassEtropyInfo; };
	std::string getAttributeName(int index) { return this->atributesName[index]; };

	
	void LoadData(std::string name);
	int numberOfLaabels(int index, std::vector<int>& indexs);
	std::vector<std::string> getDiferentLabels(int index, std::vector<int>& indexs);
	int numberOfPresence(int index, std::string value, std::vector<int>& indexs);
	void setTargetClass(int number) {
		this->targetClass = number;
	};

	std::vector<int> createSubset(std::vector<int>& indexs, int atttributeIndex, std::string value);
	bool isLeaf(std::vector<int>& indexs);
	double calculateEntropyInfo(int index, std::vector<int>& indexs);
	std::unordered_map<std::string, std::vector<int>> getLabels(int index, std::vector<int>& indexs);
	double calculateSplitInfo(int index, std::vector<int>& indexs);
	double getEntropyInfoTargetClass(std::vector<int> indexs);

private:
	void setBoolInfo();
};

