#pragma once
#include <vector>
#include <string>
class ConfusionMatrix
{
private:
	std::vector<std::vector<int>> matrix;
public:
	ConfusionMatrix() : matrix(2, std::vector<int>(2, 0)) {};
	void addPrediction(std::string actual, std::string predict);
	const std::vector<std::vector<int>> getMatrix() { return this->matrix; };
	void clearMatrix() { this->matrix.clear(); };
	int sumOfMatrix();
};

