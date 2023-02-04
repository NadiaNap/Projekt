#ifndef NAMES_DATA_H
#define NAMES_DATA_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

struct NameRecord {
    string woj;
    string voivodeship;
    string secondName;
    string gender;
    int occurrences;
};

class NamesData {

private:
    vector<NameRecord> data;
    string mostPopularName;
    int mostPopularQuantity = 0;
    void updateMostPopularNameAndQuantity(NameRecord record);

public:
    void appendDataFromFile(string fileName);
    void prepareStatisticsPerVoivodeship();
    void saveData(vector<NameRecord> data, string fileName);
    vector<NameRecord> getLoadedData();
};

#endif
