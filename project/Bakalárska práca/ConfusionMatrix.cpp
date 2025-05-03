#include "ConfusionMatrix.h"

/**
 * @brief Pridá jednu predikciu do konfúznej matice.
 *
 * Funkcia porovná skutoènú hodnotu (actual) s predikovanou hodnotou (predict)
 * a pod¾a toho inkrementuje príslušnú bunku v 2x2 konfúznej matici.
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
 * @brief Spoèíta celkový poèet záznamov v konfúznej matici.
 *
 * Prechádza všetky štyri bunky matice a vracia súèet všetkých hodnôt,
 * èo zodpovedá celkovému poètu klasifikovaných prípadov.
 *
 * @return Celkový poèet hodnotení zapísaných do konfúznej matice.
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
