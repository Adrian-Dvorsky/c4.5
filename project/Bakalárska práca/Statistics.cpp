#include "Statistics.h"

/**
 * @brief Prid· hodnotu presnosti (accuracy) do zoznamu.
 * @param value Hodnota presnosti
 */
void Statistics::addAccuracy(double value) {
    accuracy.push_back(value);
}

/**
 * @brief Prid· hodnotu presnosti (precision) do zoznamu.
 * @param value Hodnota precision
 */

void Statistics::addPrecision(double value) {
    precision.push_back(value);
}


/**
 * @brief Prid· hodnotu citlivosti (recall) do zoznamu.
 * @param value Hodnota recall
 */

void Statistics::addRecall(double value) {
    recall.push_back(value);
}

/**
 * @brief Prid· hodnotu F-skÛre do zoznamu.
 * @param value Hodnota F-skÛre
 */

void Statistics::addFscore(double value) {
    fscore.push_back(value);
}

/**
 * @brief VypoËÌta priemern˙ hodnotu presnosti (accuracy).
 * @return Priemern· hodnota presnosti alebo 0.0, ak nie je Ëo vyhodnocovaù
 */

double Statistics::getAverageAccuracy() const {
    double sum = 0.0;
    for (double val : accuracy) sum += val;
    return accuracy.empty() ? 0.0 : sum / accuracy.size();
}

/**
 * @brief VypoËÌta priemern˙ hodnotu presnosti (precision).
 * @return Priemern· hodnota precision alebo 0.0, ak nie je Ëo vyhodnocovaù
 */

double Statistics::getAveragePrecision() const {
    double sum = 0.0;
    for (double val : precision) sum += val;
    return precision.empty() ? 0.0 : sum / precision.size();
}

/**
 * @brief VypoËÌta priemern˙ hodnotu citlivosti (recall).
 * @return Priemern· hodnota recall alebo 0.0, ak nie je Ëo vyhodnocovaù
 */

double Statistics::getAverageRecall() const {
    double sum = 0.0;
    for (double val : recall) sum += val;
    return recall.empty() ? 0.0 : sum / recall.size();
}

/**
 * @brief VypoËÌta priemern˙ hodnotu F-skÛre.
 * @return Priemern· hodnota F-skÛre alebo 0.0, ak nie je Ëo vyhodnocovaù
 */

double Statistics::getAverageFscore() const {
    double sum = 0.0;
    for (double val : fscore) sum += val;
    return fscore.empty() ? 0.0 : sum / fscore.size();
}