#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant>
#include <cctype>
#include "Data.h"

int main() {
	std::string fileName = "C:\\Users\\adria\\Downloads\\heart+failure+clinical+records\\heart_failure_clinical_records_dataset.csv";
	Data data;
	data.setTargetClass(12);
	data.LoadData(fileName);
	return 0;
}