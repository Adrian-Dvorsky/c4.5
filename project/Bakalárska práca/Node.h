#pragma once
#include <string>
#include <map>
#include <vector>
class Node
{
private:
	bool isLeaf;
	std::string label;
	std::string nodeValue;
	int splitAttribute;
	double splitThreshold;
	std::vector<Node*> children;
	std::string targetClassValue;
	std::string majorityClass;
	int numSamples;
	double informationGain;
public:
	/**
	 * @brief Kon�truktor uzla, inicializuje ako nelistov� s predvolen�mi hodnotami.
	 */
	Node() : isLeaf(false), splitAttribute(-1), splitThreshold(-1), majorityClass("") {};

	/**
	 * @brief De�truktor uzla.
	 */
	~Node();

	/**
	* @brief Zist�, �i je uzol listom.
	*/
	bool getLeaf() { return this->isLeaf; };
	
	/**
	 * @brief Nastav�, �i je uzol listom.
	 * @param state True ak ide o list, inak false.
	 */
	void setLeaf(bool state) { this->isLeaf = state; };
	
	/**
	 * @brief Z�ska n�zov atrib�tu, pod�a ktor�ho sa vetv�.
	 */
	std::string getLabel() { return this->label; };
	
	/**
	 * @brief Nastav� n�zov atrib�tu, pod�a ktor�ho sa vetv�.
	 * @param name N�zov atrib�tu.
	 */
	void setLabel(std::string name) { this->label = name; };
	
	/**
	 * @brief Z�ska prahov� hodnotu vetvenia pre ��seln� atrib�t.
	 */
	double getTreshold() { return this->splitThreshold; };
	
	/**
	 * @brief Nastav� prahov� hodnotu vetvenia.
	 * @param splitThreshold Hodnota prahu.
	 */
	void setTreshold(double splitThreshold) { this->splitThreshold = splitThreshold; };
	
	/**
	 * @brief Z�ska index atrib�tu, pod�a ktor�ho sa uzol rozde�uje.
	 */
	int getSplitAttribute() { return this->splitAttribute; };
	
	/**
	 * @brief Nastav� index atrib�tu pre rozdelenie.
	 * @param value Index atrib�tu.
	 */
	void setSplitAttribute(int value) { this->splitAttribute = value; };
	
	/**
	 * @brief Z�ska cie�ov� triedu pre listov� uzol.
	 */
	std::string getTargetClassValue() { return this->targetClassValue; };
	
	/**
	 * @brief Nastav� cie�ov� triedu pre listov� uzol.
	 * @param value Hodnota cie�ovej triedy.
	 */
	void setTargetClassValue(std::string value) { this->targetClassValue = value; };
	
	/**
	* @brief Z�ska naj�astej�iu triedu v uzle.
	*/
	std::string getMajorityClass() { return this->majorityClass; };
	
	/**
	* @brief Nastav� naj�astej�iu triedu v uzle.
	* @param value N�zov triedy.
	*/
	void setMajorityClass(std::string value) { this->majorityClass = value; };
	
	/**
	 * @brief Z�ska hodnotu atrib�tu, ktor� viedla do tohto uzla.
	 */
	std::string getNodeValue() { return this->nodeValue; };

	/**
	 * @brief Nastav� hodnotu atrib�tu, ktor� viedla do tohto uzla.
	 * @param value Hodnota z nadraden�ho uzla.
	 */
	void setNodeValue(std::string value) { this->nodeValue = value; };

	/**
	 * @brief Prid� potomka k uzlu.
	 * @param node Ukazovate� na die�a.
	 */
	void addChild(Node* node);

	/**
	 * @brief Vr�ti die�a na zadanom indexe.
	 */
	Node* getChild(int index) { return children[index]; };

	/**
	 * @brief Vr�ti po�et potomkov uzla.
	 */
	int getNumberOfChildren() { return children.size(); };
	
	/**
	 * @brief Odstr�ni die�a na danom indexe.
	 */
	void removeChild(int index) {
		if (index < 0 || index >= children.size()) {
			return;
		}
		children.erase(children.begin() + index);
	}

	/**
	 * @brief Z�ska po�et vzoriek, ktor� pre�li t�mto uzlom.
	 */
	int getNumSamples() { return this->numSamples; };
	
	/**
	 * @brief Nastav� po�et vzoriek pre tento uzol.
	 * @param value Po�et vzoriek.
	 */
	void setNumSamples(int value) { this->numSamples = value; };
	
	/**
	 * @brief Z�ska informa�n� zisk dan�ho uzla.
	 */
	double getInformationGain() { return this->informationGain; };
	
	/**
	 * @brief Nastav� informa�n� zisk pre uzol.
	 * @param value Hodnota information gain.
	 */
	void setInformationGain(double value) { this->informationGain = value; };
	
	/**
	 * @brief Vr�ti zoznam v�etk�ch potomkov.
	 */
	const std::vector<Node*> getChildren() { return this->children; };
};

