#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Data
{
private:
	std::vector<std::vector<std::string>> data;
	std::vector<std::string> atributesName;
	int targetClass;
public:
	void LoadData(std::string name);
	int numberOfLaabels(int index);
	void setTargetClass(int number) {
		this->targetClass = number;
	}
};

