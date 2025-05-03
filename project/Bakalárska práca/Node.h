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
	 * @brief Konötruktor uzla, inicializuje ako nelistov˝ s predvolen˝mi hodnotami.
	 */
	Node() : isLeaf(false), splitAttribute(-1), splitThreshold(-1), majorityClass("") {};

	/**
	 * @brief Deötruktor uzla.
	 */
	~Node();

	/**
	* @brief ZistÌ, Ëi je uzol listom.
	*/
	bool getLeaf() { return this->isLeaf; };
	
	/**
	 * @brief NastavÌ, Ëi je uzol listom.
	 * @param state True ak ide o list, inak false.
	 */
	void setLeaf(bool state) { this->isLeaf = state; };
	
	/**
	 * @brief ZÌska n·zov atrib˙tu, podæa ktorÈho sa vetvÌ.
	 */
	std::string getLabel() { return this->label; };
	
	/**
	 * @brief NastavÌ n·zov atrib˙tu, podæa ktorÈho sa vetvÌ.
	 * @param name N·zov atrib˙tu.
	 */
	void setLabel(std::string name) { this->label = name; };
	
	/**
	 * @brief ZÌska prahov˙ hodnotu vetvenia pre ËÌseln˝ atrib˙t.
	 */
	double getTreshold() { return this->splitThreshold; };
	
	/**
	 * @brief NastavÌ prahov˙ hodnotu vetvenia.
	 * @param splitThreshold Hodnota prahu.
	 */
	void setTreshold(double splitThreshold) { this->splitThreshold = splitThreshold; };
	
	/**
	 * @brief ZÌska index atrib˙tu, podæa ktorÈho sa uzol rozdeæuje.
	 */
	int getSplitAttribute() { return this->splitAttribute; };
	
	/**
	 * @brief NastavÌ index atrib˙tu pre rozdelenie.
	 * @param value Index atrib˙tu.
	 */
	void setSplitAttribute(int value) { this->splitAttribute = value; };
	
	/**
	 * @brief ZÌska cieæov˙ triedu pre listov˝ uzol.
	 */
	std::string getTargetClassValue() { return this->targetClassValue; };
	
	/**
	 * @brief NastavÌ cieæov˙ triedu pre listov˝ uzol.
	 * @param value Hodnota cieæovej triedy.
	 */
	void setTargetClassValue(std::string value) { this->targetClassValue = value; };
	
	/**
	* @brief ZÌska najËastejöiu triedu v uzle.
	*/
	std::string getMajorityClass() { return this->majorityClass; };
	
	/**
	* @brief NastavÌ najËastejöiu triedu v uzle.
	* @param value N·zov triedy.
	*/
	void setMajorityClass(std::string value) { this->majorityClass = value; };
	
	/**
	 * @brief ZÌska hodnotu atrib˙tu, ktor· viedla do tohto uzla.
	 */
	std::string getNodeValue() { return this->nodeValue; };

	/**
	 * @brief NastavÌ hodnotu atrib˙tu, ktor· viedla do tohto uzla.
	 * @param value Hodnota z nadradenÈho uzla.
	 */
	void setNodeValue(std::string value) { this->nodeValue = value; };

	/**
	 * @brief Prid· potomka k uzlu.
	 * @param node Ukazovateæ na dieùa.
	 */
	void addChild(Node* node);

	/**
	 * @brief Vr·ti dieùa na zadanom indexe.
	 */
	Node* getChild(int index) { return children[index]; };

	/**
	 * @brief Vr·ti poËet potomkov uzla.
	 */
	int getNumberOfChildren() { return children.size(); };
	
	/**
	 * @brief Odstr·ni dieùa na danom indexe.
	 */
	void removeChild(int index) {
		if (index < 0 || index >= children.size()) {
			return;
		}
		children.erase(children.begin() + index);
	}

	/**
	 * @brief ZÌska poËet vzoriek, ktorÈ preöli t˝mto uzlom.
	 */
	int getNumSamples() { return this->numSamples; };
	
	/**
	 * @brief NastavÌ poËet vzoriek pre tento uzol.
	 * @param value PoËet vzoriek.
	 */
	void setNumSamples(int value) { this->numSamples = value; };
	
	/**
	 * @brief ZÌska informaËn˝ zisk danÈho uzla.
	 */
	double getInformationGain() { return this->informationGain; };
	
	/**
	 * @brief NastavÌ informaËn˝ zisk pre uzol.
	 * @param value Hodnota information gain.
	 */
	void setInformationGain(double value) { this->informationGain = value; };
	
	/**
	 * @brief Vr·ti zoznam vöetk˝ch potomkov.
	 */
	const std::vector<Node*> getChildren() { return this->children; };
};

