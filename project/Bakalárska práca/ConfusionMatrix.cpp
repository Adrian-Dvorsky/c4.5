#include "ConfusionMatrix.h"

void ConfusionMatrix::addPrediction(std::string actual, std::string predict)
{
	if (actual == "1" || actual == "TRUE" || actual == "true") {
		if (predict == "1" || predict == "TRUE" || predict == "true") {
			this->matrix[0][0]++;
		}
		else {
			this->matrix[1][0]++;
		}
	}
	else {
		if (predict == "0" || predict == "FALSE" || predict == "false") {
			this->matrix[1][1]++;
		}
		else {
			this->matrix[0][1]++;
		}
	}
}

int ConfusionMatrix::sumOfMatrix()
{
	int sum = 0;
	for (int i = 0; i < this->matrix.size(); i++) {
		for (int j = 0; j < this->matrix[i].size(); j++) {
			sum += this->matrix[i][j];
		}
	}
	return sum;
}
