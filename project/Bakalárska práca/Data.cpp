#include "Data.h"
#include <unordered_set>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cctype>
#include <regex>
/**
 * @brief Na��ta d�ta zo s�boru a ulo�� vybran� st�pce.
 *
 * Prv� dva riadky v s�bore obsahuj� n�zvy atrib�tov a typy atrib�tov.
 * Funkcia na��ta len tie st�pce, ktor�ch indexy s� uveden� v indexs.
 * @param name N�zov CSV s�boru
 * @param indexs Indexy st�pcov, ktor� sa maj� na��ta�
 * @return true ak sa s�bor podarilo na��ta�, inak false
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
 * @brief Na��ta len n�zvy atrib�tov z prv�ho riadku CSV s�boru.
 * @param name N�zov CSV s�boru
 * @return true ak sa n�zvy na��tali �spe�ne, inak false
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
 * @brief Spo��ta po�et v�skytov hodnoty v danom atrib�te medzi zadan�mi indexmi.
 * @param index Index atrib�tu
 * @param value Hodnota, ktorej v�skyt sa po��ta
 * @param indexs Indexy vzoriek, ktor� sa maj� pou�i�
 * @return Po�et v�skytov hodnoty
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
 * @brief Zist� po�et unik�tnych hodn�t triedy na danom indexe.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @return Po�et unik�tnych hodn�t triedy
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
 * @brief Z�ska r�zne hodnoty triedy pre dan� atrib�t a indexy.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @return Vektor unik�tnych hodn�t triedy
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
 * @brief Vytvor� podmno�inu indexov, ktor� maj� konkr�tnu hodnotu atrib�tu.
 * @param indexs Indexy p�vodn�ch vzoriek
 * @param atttributeIndex Index atrib�tu
 * @param value Hodnota, ktor� m� atrib�t ma�
 * @return Vektor nov�ch indexov zodpovedaj�cich podmienke
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
 * @brief Vytvor� podmno�inu indexov na z�klade ��seln�ho prahu atrib�tu.
 * @param indexs Indexy vzoriek
 * @param atttributeIndex Index atrib�tu
 * @param treshold Prahov� hodnota
 * @param isHigher Ak true, vracia hodnoty v��ie ne� prah, inak men�ie alebo rovn�
 * @return Vektor indexov sp��aj�cich podmienku
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
 * @brief Zist�, �i v�etky vzorky patria do rovnakej triedy.
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
 * @brief Vypo��ta entropiu triedy po rozdelen� pod�a hodnoty atrib�tu.
 * @param index Index atrib�tu
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
 * @brief Zoskup� indexy pod�a hodn�t atrib�tu.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @return Mapa hodn�t atrib�tu na indexy vzoriek
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
 * @brief Vypo��ta split info pre gain ratio.
 * @param index Index atrib�tu
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
 * @brief Vypo��ta entropiu cie�ovej triedy pred rozdelen�m.
 * @param indexs Indexy vzoriek
 * @return Hodnota entropie cie�ovej triedy
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
 * @brief Zist�, �i v�etky hodnoty atrib�tu s� rovnak�.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @return true ak s� v�etky hodnoty rovnak�, inak false
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
 * @brief Vypo��ta gain ratio pre dan� atrib�t.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @return Vektor s hodnotami [gain ratio, prahov� hodnota, information gain]
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
 * @brief H�ad� najlep�� prah pre ��seln� atrib�t na z�klade gain ratio.
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @param isIntiger true ak je atrib�t cel� hodnota, inak false
 * @return Vektor s hodnotami [najlep�� gain ratio, prah, information gain]
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
 * @brief Rozdel� indexy pod�a prahovej hodnoty (<= alebo >).
 * @param index Index atrib�tu
 * @param indexs Indexy vzoriek
 * @param isHigher Ak true, vyberie v��ie hodnoty, inak men�ie alebo rovn�
 * @param treshold Prahov� hodnota
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
 * @brief N�jde naj�astej�ie sa vyskytuj�cu triedu medzi vzorkami.
 * @param indexs Indexy vzoriek
 * @return N�zov naj�astej�ej triedy
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





