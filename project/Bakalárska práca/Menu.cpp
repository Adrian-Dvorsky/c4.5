#include "Menu.h"
#include <iostream>
#include <string>
#include "Data.h"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>

/**
 * @brief Kon�truktor � Inicializuje objekt Data a spust� hlavn� menu.
 */
Menu::Menu()
{
	if (this->data == nullptr) {
		this->data = new Data();
	}
	this->spustiProgram();
}

/**
 * @brief Destruktor � Uvo�n� alokovan� pam� pre Data a Tree.
 */

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

/**
 * @brief Na��ta od pou��vate�a indexy st�pcov, ktor� chce importova� zo s�boru.
 * @return Vektor indexov (zmen�en� o -1 pre nulov� indexovanie).
 */

std::vector<int> Menu::loadIndexs()
{
	std::string dummy;
	std::getline(std::cin, dummy);
	std::string input;
	std::getline(std::cin, input);

	std::stringstream ss_input(input);
	std::vector<int> columns_to_read;
	int col;

	while (ss_input >> col) {
		columns_to_read.push_back(col - 1);
	}

	return columns_to_read;
}

/**
 * @brief Pomocn� funkcia � Konvertuje wstring na std::string.
 * @param wstr �irok� re�azec (wstring)
 * @return Re�azec v UTF-8 (std::string)
 */

std::string wstringToString(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(wstr);
}

/**
 * @brief Zobraz� dial�gov� okno pre v�ber CSV s�boru.
 * @return Cesta k vybran�mu s�boru alebo pr�zdny re�azec pri zru�en�.
 */
std::string openFileDialog() {
	wchar_t filename[MAX_PATH] = L"";

	OPENFILENAMEW ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = L"CSV Files\0*.csv\0All Files\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.lpstrTitle = L"Vyber CSV s�bor";

	if (GetOpenFileNameW(&ofn)) {
		return wstringToString(std::wstring(filename));
	}
	else {
		return "";
	}
}

/**
 * @brief Spust� hlavn� menu aplik�cie, na��ta s�bor, atrib�ty a vytr�nuje rozhodovac� strom.
 *
 * Pou��vate� si m��e zvoli� bu� v�etky atrib�ty, alebo vlastn� v�ber,
 * n�sledne sa vykon� na��tanie d�t a spustenie tr�novania.
 */

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
	std::string filepath = openFileDialog();
	if (this->data == nullptr) {
		this->data = new Data();
	}
	if (!data->loadNames(filepath)) {
		std::cout << "--------------     Zadal si zly nazov subor" << std::endl;
		this->spustiProgram();
	}
	else {
		std::cout << "--------------     Vyber si moznost" << std::endl;
		std::cout << "--------------     1. Vsetky atributy" << std::endl;
		std::cout << "--------------     2. Vlastny vyber" << std::endl;
		int vyber; 
		std::cin >> vyber;
		std::vector<int> indexs; 
		const std::vector<std::string> names = data->getAttributesNames();
		if (vyber == 1) {
			for (int i = 0; i < names.size(); i++) {
				indexs.push_back(i);
			}
		}
		else {
			std::cout << "--------------     Vyber si vstupne atributy" << std::endl;

			for (int i = 0; i < names.size() - 1; i++) {
				std::cout << "     " << i + 1 << " " << names[i] << std::endl;
			}
			indexs = this->loadIndexs();
			indexs.push_back(names.size() - 1);
		}
		data->LoadData(filepath, indexs);
		int size = data->getSize();
		this->tree = new Tree(this->data);
		this->data->setTargetClass(data->getNumberOfAttributes() - 1);
		this->tree->startBuilding();
	}
}