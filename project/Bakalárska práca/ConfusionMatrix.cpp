#include "ConfusionMatrix.h"

/**
 * @brief Prid� jednu predikciu do konf�znej matice.
 *
 * Funkcia porovn� skuto�n� hodnotu (actual) s predikovanou hodnotou (predict)
 * a pod�a toho inkrementuje pr�slu�n� bunku v 2x2 konf�znej matici.
 *  
 */

void ConfusionMatrix::addPrediction(std::string actual, std::string predict)
{
	if (actual == "1" || actual == "TRUE" || actual == "true" || actual == "Yes") {
		if (predict == "1" || predict == "TRUE" || predict == "true" || predict == "Yes") {
			this->matrix[0][0]++;
		}
		else {
			this->matrix[1][0]++;
		}
	}
	else {
		if (predict == "0" || predict == "FALSE" || predict == "false" || predict == "No") {
			this->matrix[1][1]++;
		}
		else {
			this->matrix[0][1]++;
		}
	}
}

/**
 * @brief Spo��ta celkov� po�et z�znamov v konf�znej matici.
 *
 * Prech�dza v�etky �tyri bunky matice a vracia s��et v�etk�ch hodn�t,
 * �o zodpoved� celkov�mu po�tu klasifikovan�ch pr�padov.
 *
 * @return Celkov� po�et hodnoten� zap�san�ch do konf�znej matice.
 */

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
