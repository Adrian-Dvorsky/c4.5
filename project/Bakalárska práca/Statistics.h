#pragma once
#include <vector>

class Statistics
{
	std::vector<double> accuracy;
	std::vector<double> precision;
	std::vector<double> recall;
	std::vector<double> fscore;
public:
    void addAccuracy(double value);
    void addPrecision(double value);
    void addRecall(double value);
    void addFscore(double value);

    double getAverageAccuracy() const;
    double getAveragePrecision() const;
    double getAverageRecall() const;
    double getAverageFscore() const;
};

