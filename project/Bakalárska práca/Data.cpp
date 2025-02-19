#include "Data.h"
#include <unordered_set>

void Data::LoadData(std::string name)
{
	std::ifstream file(name);
	if (!file.is_open()) {
		std::cout << "Chyba\n" << std::endl;
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);

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

int Data::numberOfLaabels(int index)
{
	std::unordered_set<std::string> unique;
	for (int i = 1; i < this->data[index].size(); i++) {
		unique.insert(this->data[index][i]);
	}
	return unique.size();
}
