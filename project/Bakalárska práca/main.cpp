#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant>
#include <cctype>
#include "Data.h"
#include "Tree.h"

int main() {
	std::string fileName = "C:\\Users\\adria\\Downloads\\heart+failure+clinical+records\\test.csv";
	Data data;
	data.setTargetClass(3);
	data.LoadData(fileName);
	Tree * tree = new Tree(&data);
	std::vector<int> numbers;
	for (int i = 0; i < data.getSize(); i++) {
		numbers.push_back(i);
	}
	std::vector<bool> availableAttributes;
	for (int i = 0; i < data.getNumberOfAttributes() - 1; i++)
	{
		availableAttributes.push_back(true);
	}
 	tree->buildTree(tree->getRoot(), numbers, availableAttributes);
	return 0;
}