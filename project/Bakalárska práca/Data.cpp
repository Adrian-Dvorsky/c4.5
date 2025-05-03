#include "Data.h"
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cctype>
#include <regex>
/**
 * @brief Naèíta dáta zo súboru a uloí vybrané ståpce.
 *
 * Prvé dva riadky v súbore obsahujú názvy atribútov a typy atribútov.
 * Funkcia naèíta len tie ståpce, ktorıch indexy sú uvedené v indexs.
 * @param name Názov CSV súboru
 * @param indexs Indexy ståpcov, ktoré sa majú naèíta
 * @return true ak sa súbor podarilo naèíta, inak false
 */
bool Data::LoadData(std::string& name, std::vector<int> indexs)
{
	std::ifstream file(name);
	if (!file.is_open()) {
		return false;
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string value; 
	int colIndex = 0;
	while (std::getline(ss, value, ',')) {
		if (std::find(indexs.begin(), indexs.end(), colIndex) != indexs.end()) {
			this->atributesName.push_back(value);
		}
		++colIndex;
	}
	std::getline(file, line);
	std::stringstream sss(line);
	colIndex = 0;
	while (std::getline(sss, value, ',')) {
		if (std::find(indexs.begin(), indexs.end(), colIndex) != indexs.end()) {
			this->atributeType.push_back(value);
		}
		++colIndex;
	}
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string value;
		std::vector<std::string> rowData;
		colIndex = 0;
		while (std::getline(ss, value, ',')) {
			if (std::find(indexs.begin(), indexs.end(), colIndex) != indexs.end()) {
				rowData.push_back(value);
			}
			++colIndex;
		}
		this->data.push_back(rowData);
	}
	file.close();
	return true;
}

/**
 * @brief Naèíta len názvy atribútov z prvého riadku CSV súboru.
 * @param name Názov CSV súboru
 * @return true ak sa názvy naèítali úspešne, inak false
 */

bool Data::loadNames(std::string& name)
{
	std::ifstream file(name);
	if (!file.is_open()) {
		return false;
	}
	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string value;
	while (std::getline(ss, value, ',')) {
		this->atributesName.push_back(value);
	}
	file.close();
	return true;
}

/**
 * @brief Spoèíta poèet vıskytov hodnoty v danom atribúte medzi zadanımi indexmi.
 * @param index Index atribútu
 * @param value Hodnota, ktorej vıskyt sa poèíta
 * @param indexs Indexy vzoriek, ktoré sa majú poui
 * @return Poèet vıskytov hodnoty
 */

int Data::numberOfPresence(int index, std::string value, std::vector<int>& indexs)
{
	int number = 0;
	for (int i = 0; i < indexs.size(); i++) {
		if (value == this->data[indexs[i]][index]) {
			number++;
		}
	}
	return number;
}
/**
 * @brief Zistí poèet unikátnych hodnôt triedy na danom indexe.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Poèet unikátnych hodnôt triedy
 */

int Data::numberOfLaabels(int index, std::vector<int>& indexs)
{
	std::unordered_set<std::string> unique;
	for (int i = 1; i < indexs.size(); i++) {
		unique.insert(this->data[index][indexs[i]]);
	}
	return unique.size();
}

/**
 * @brief Získa rôzne hodnoty triedy pre danı atribút a indexy.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Vektor unikátnych hodnôt triedy
 */

std::vector<std::string> Data::getDiferentLabels(int index, std::vector<int>& indexs)
{
	std::unordered_set<std::string> unique;
	for (int i = 0; i < indexs.size(); i++) {
		unique.insert(this->data[indexs[i]][index]);
	}

	std::vector<std::string> labels(unique.begin(), unique.end());
	return labels;
}

/**
 * @brief Destruktor triedy Data.
 */
Data::~Data()
{

}

/**
 * @brief Vytvorí podmnoinu indexov, ktoré majú konkrétnu hodnotu atribútu.
 * @param indexs Indexy pôvodnıch vzoriek
 * @param atttributeIndex Index atribútu
 * @param value Hodnota, ktorú má atribút ma
 * @return Vektor novıch indexov zodpovedajúcich podmienke
 */

std::vector<int> Data::createSubset(std::vector<int>& indexs, int atttributeIndex, std::string value)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		std::string test = this->data[indexs[i]][atttributeIndex];
		if (this->data[indexs[i]][atttributeIndex] == value) {
			newIndexs.push_back(indexs[i]);
		}
	}
	return newIndexs;
}

/**
 * @brief Vytvorí podmnoinu indexov na základe èíselného prahu atribútu.
 * @param indexs Indexy vzoriek
 * @param atttributeIndex Index atribútu
 * @param treshold Prahová hodnota
 * @param isHigher Ak true, vracia hodnoty väèšie ne prah, inak menšie alebo rovné
 * @return Vektor indexov spåòajúcich podmienku
 */
std::vector<int> Data::createSubsetForNumbers(std::vector<int>& indexs, int atttributeIndex, double treshold, bool isHigher)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		double value = std::stod(this->data[indexs[i]][atttributeIndex]);
		if (isHigher) {
			if (value > treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
		else {
			if (value <= treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
	}
	return newIndexs;
}

/**
 * @brief Zistí, èi všetky vzorky patria do rovnakej triedy.
 * @param indexs Indexy vzoriek
 * @return true ak patria do rovnakej triedy, inak false
 */

bool Data::isLeaf(std::vector<int>& indexs)
{
	if (indexs.size() == 1) {
		return true;
	}
	std::string value = this->data[indexs[0]][this->targetClass];
	for (int i = 1; i < indexs.size(); i++) {
		if (this->data[indexs[i]][this->targetClass] != value) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Vypoèíta entropiu triedy po rozdelení pod¾a hodnoty atribútu.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Hodnota entropie
 */
double Data::calculateEntropyInfo(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(index, indexs);
	double entropy = 0.0;
	for (auto& partHast : hashMap) {
		std::vector<std::string> labels = this->getDiferentLabels(this->targetClass, indexs);
		std::vector<int> numberOfPresence;
		double partialEntropy = 0.0;
		for (int i = 0; i < labels.size(); i++) {
			numberOfPresence.push_back(this->numberOfPresence(this->targetClass, labels[i], partHast.second));
		}
		for (int i = 0; i < numberOfPresence.size(); i++) {
			if (numberOfPresence[i] != 0) {
				double p = (double)numberOfPresence[i] / (partHast.second.size());
				partialEntropy += -p * log2(p);
			}
		}
		entropy += ((double)partHast.second.size() / indexs.size()) * partialEntropy;
	}
	return entropy;
}

/**
 * @brief Zoskupí indexy pod¾a hodnôt atribútu.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Mapa hodnôt atribútu na indexy vzoriek
 */

std::unordered_map<std::string, std::vector<int>> Data::getLabels(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap;
	for (int i = 0; i < indexs.size(); i++) {
		hashMap[this->data[indexs[i]][index]].push_back(indexs[i]);
	}
	return hashMap;
}

/**
 * @brief Vypoèíta split info pre gain ratio.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Hodnota split info
 */

double Data::calculateSplitInfo(int index, std::vector<int>& indexs)
{
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(index, indexs);
	double splitInfo = 0.0;
	for (auto& value : hashMap) {
		double p = (double) value.second.size()/ (indexs.size());
		splitInfo += -p * log2(p);
	}
	return splitInfo;
}

/**
 * @brief Vypoèíta entropiu cie¾ovej triedy pred rozdelením.
 * @param indexs Indexy vzoriek
 * @return Hodnota entropie cie¾ovej triedy
 */

double Data::getEntropyInfoTargetClass(std::vector<int> indexs)
{
	double entropy = 0.0;
	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(this->targetClass, indexs);
	for (auto& value : hashMap) {
		double p = (double)value.second.size() / (indexs.size());
		entropy += -p * log2(p);
	}
	return entropy;
}

/**
 * @brief Zistí, èi všetky hodnoty atribútu sú rovnaké.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return true ak sú všetky hodnoty rovnaké, inak false
 */

bool Data::isHomogene(int index, std::vector<int>& indexs)
{
	std::string value = this->data[indexs[0]][index];
	for (int i = 0; i < indexs.size(); i++) {
		if (value != this->data[indexs[i]][index]) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Vypoèíta gain ratio pre danı atribút.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @return Vektor s hodnotami [gain ratio, prahová hodnota, information gain]
 */

std::vector<double> Data::getGainTest(int index, std::vector<int>& indexs)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<double> gainRatio;
	if (this->atributeType[index] == "i") {
		return this->findTreshold(index, indexs, true);
	}
	else if (this->atributeType[index] == "d") {
		return this->findTreshold(index, indexs, false);
	}
	else {
		double informationGain = targetClassEntropy - this->calculateEntropyInfo(index, indexs);
		if (informationGain < 0.0000001) {
			informationGain = 0;
		}
		double splitInfo = this->calculateSplitInfo(index, indexs);
		double gainRatio = 0.0;
		if (splitInfo == 0) {
			gainRatio = 0;
		}
		else {
			gainRatio = informationGain / splitInfo;
		}
		std::vector<double> retVector;
		retVector.push_back(gainRatio);
		retVector.push_back(std::numeric_limits<double>::quiet_NaN());
		retVector.push_back(informationGain);
		return retVector;
	}
}

/**
 * @brief H¾adá najlepší prah pre èíselnı atribút na základe gain ratio.
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @param isIntiger true ak je atribút celá hodnota, inak false
 * @return Vektor s hodnotami [najlepší gain ratio, prah, information gain]
 */

std::vector<double> Data::findTreshold(int index, std::vector<int>& indexs, bool isIntiger)
{
	double targetClassEntropy = this->getEntropyInfoTargetClass(indexs);
	std::vector<double> newData;
	for (int i = 0; i < indexs.size(); i++) {
		newData.push_back(std::stod(this->data[indexs[i]][index]));
	}
	std::sort(newData.begin(), newData.end());
	std::vector<double> tresholds;
	for (int i = 0; i < indexs.size() -1; i++) {
		if (newData[i] != newData[i + 1]) {
			if (isIntiger) {
				tresholds.push_back(std::round((newData[i] + newData[i + 1]) / 2));
			}
			else {
				tresholds.push_back((newData[i] + newData[i + 1]) / 2);
			}
		}
	}
	double bestTreshold = -1;
	double bestGainRatio = -1;
	double informationGain = -1;
	for (int i = 0; i < tresholds.size(); i++) {
		std::vector<std::string> labels = this->getDiferentLabels(this->targetClass, indexs);
		std::vector<int> leftInterval = this->createIndexsForTreshold(index, indexs, false, tresholds[i]);
		std::vector<int> rightInterval = this->createIndexsForTreshold(index, indexs, true, tresholds[i]);
		double entropy = 0.0;
		double partialEntropy = 0.0;
		std::vector<int> numberOfPresenceLeft;
		std::vector<int> numberOfPresenceRight;
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceLeft.push_back(this->numberOfPresence(this->targetClass, labels[j], leftInterval));
		}
		for (int j = 0; j < labels.size(); j++) {
			numberOfPresenceRight.push_back(this->numberOfPresence(this->targetClass, labels[j], rightInterval));
		}
		for (int j = 0; j < numberOfPresenceLeft.size(); j++) {
			if (numberOfPresenceLeft[j] != 0) {
				double p = (double)numberOfPresenceLeft[j] / (std::accumulate(numberOfPresenceLeft.begin(), numberOfPresenceLeft.end(), 0));
				if (p > 0) {
					partialEntropy += -p * log2(p);
				}
			}
		}
		entropy += ((double)std::accumulate(numberOfPresenceLeft.begin(), numberOfPresenceLeft.end(), 0) / indexs.size()) * partialEntropy;
		partialEntropy = 0;
		for (int j = 0; j < numberOfPresenceRight.size(); j++) {
			if (numberOfPresenceRight[j] != 0) {
				double p = (double)numberOfPresenceRight[j] / (std::accumulate(numberOfPresenceRight.begin(), numberOfPresenceRight.end(), 0));
				if (p > 0) {
					partialEntropy += -p * log2(p);
				}
			}
		}
		entropy += ((double)std::accumulate(numberOfPresenceRight.begin(), numberOfPresenceRight.end(), 0) / indexs.size()) * partialEntropy;
		double gain = targetClassEntropy - entropy;
		if (gain < 0.0000001) {
			gain = 0;
		}
		double splitInfo = 0.0;
		double p = ((double)leftInterval.size() / indexs.size());
		if (p > 0) {
			splitInfo += -p * log2(p);
		}
		if (p > 0) {
			p = ((double)rightInterval.size() / indexs.size());
		}
		splitInfo += -p * log2(p);
		double gainRatio = 0.0;
		if (splitInfo != 0) {
			gainRatio = gain / splitInfo;
		}
		if (gainRatio > bestGainRatio) {
			bestGainRatio = gainRatio;
			bestTreshold = tresholds[i];
			informationGain = gain;
		}
	}
	std::vector<double> returnVector;
	if (bestGainRatio == -1) {
		returnVector.push_back(0);
	}
	else {
		returnVector.push_back(bestGainRatio);
	}
	returnVector.push_back(bestTreshold);
	returnVector.push_back(informationGain);
	return returnVector;

}

/**
 * @brief Rozdelí indexy pod¾a prahovej hodnoty (<= alebo >).
 * @param index Index atribútu
 * @param indexs Indexy vzoriek
 * @param isHigher Ak true, vyberie väèšie hodnoty, inak menšie alebo rovné
 * @param treshold Prahová hodnota
 * @return Vektor indexov vzoriek
 */

std::vector<int> Data::createIndexsForTreshold(int index, std::vector<int>& indexs, bool isHigher, double treshold)
{
	std::vector<int> newIndexs;
	for (int i = 0; i < indexs.size(); i++) {
		double value = std::stod(this->data[indexs[i]][index]);
		if (isHigher) {
			if (value > treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
		else {
			if (value <= treshold) {
				newIndexs.push_back(indexs[i]);
			}
		}
	}
	return newIndexs;
}

/**
 * @brief Nájde najèastejšie sa vyskytujúcu triedu medzi vzorkami.
 * @param indexs Indexy vzoriek
 * @return Názov najèastejšej triedy
 */

std::string Data::findMajorityClass(std::vector<int>& indexs)
{

	std::unordered_map<std::string, std::vector<int>> hashMap = this->getLabels(this->targetClass, indexs);
	std::string value;
	int max = -1;
	for (auto& partHash : hashMap) {
		int test = partHash.second.size();
		if (test > max) {
			max = partHash.second.size();
			value = partHash.first;
		}
	}
	return value;
}





