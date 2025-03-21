#include "Menu.h"
#include <iostream>
#include <string>
#include "Data.h"
Menu::Menu()
{
	if (this->data == nullptr) {
		this->data = new Data();
	}
	this->spustiProgram();
}

void Menu::spustiProgram()
{
	std::cout << "--------------     Vitaj v hlavnom menu" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "--------------     Vyber jednu z moznosti" << std::endl;
	std::cout << "--------------     1. nacitat dataset" << std::endl;
	std::cout << "--------------     2. ukoncit program" << std::endl;
	int vstup;
	std::cin >> vstup;
	if (vstup == 2) {
		return;
	}
	std::cout << "--------------     Zadaj vstupny subor" << std::endl;
	std::string vstupnySubor = "C:\\Users\\adria\\Downloads\\machine_failure\\data.csv";
	//std::cin >> vstupnySubor;
	if (this->data == nullptr) {
		this->data = new Data();
	}
	if (!data->LoadData(vstupnySubor)) {
		std::cout << "--------------     Zadal si zly nazov subor" << std::endl;
		this->spustiProgram();
	}
	else {
		this->tree = new Tree(this->data);
		this->data->setTargetClass(data->getNumberOfAttributes() - 1);
		this->tree->startBuilding();
	}
}

Menu::~Menu()
{
	if (this->data != nullptr) {
		delete this->data;
		this->data = nullptr;
	}
	if (this->tree != nullptr) {
		delete this->tree;
		this->tree = nullptr;
	}
}
