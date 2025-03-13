#include "Statistics.h"

void Statistics::addAccuracy(double value) {
    accuracy.push_back(value);
}

void Statistics::addPrecision(double value) {
    precision.push_back(value);
}

void Statistics::addRecall(double value) {
    recall.push_back(value);
}

void Statistics::addFscore(double value) {
    fscore.push_back(value);
}

double Statistics::getAverageAccuracy() const {
    double sum = 0.0;
    for (double val : accuracy) sum += val;
    return accuracy.empty() ? 0.0 : sum / accuracy.size();
}

double Statistics::getAveragePrecision() const {
    double sum = 0.0;
    for (double val : precision) sum += val;
    return precision.empty() ? 0.0 : sum / precision.size();
}

double Statistics::getAverageRecall() const {
    double sum = 0.0;
    for (double val : recall) sum += val;
    return recall.empty() ? 0.0 : sum / recall.size();
}

double Statistics::getAverageFscore() const {
    double sum = 0.0;
    for (double val : fscore) sum += val;
    return fscore.empty() ? 0.0 : sum / fscore.size();
}