#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant>
#include <cctype>
#include "Data.h"
#include "Tree.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


int main() {
	std::string fileName = "C:\\Users\\adria\\Downloads\\heart+failure+clinical+records\\heart_failure_clinical_records_dataset.csv";
	Data* data = new Data();
	data->LoadData(fileName);
	data->setTargetClass(data->getNumberOfAttributes() - 1);
	Tree * tree = new Tree(data);
	tree->startBuilding();
	delete tree;
	if (data != nullptr) {
		delete data;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}