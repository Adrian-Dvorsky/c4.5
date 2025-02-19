#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant>
#include <cctype>
#include "Data.h"

int main() {
	std::string fileName = "C:\\Users\\adria\\Downloads\\heart+failure+clinical+records\\data.csv";
	Data data;
	data.LoadData(fileName);
	int number = data.numberOfLaabels(1);
	return 0;
}