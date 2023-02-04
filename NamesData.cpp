#include "NamesData.h"

void NamesData::appendDataFromFile(string fileName){
    ifstream file(fileName);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        size_t pos = 0;
        string field;
        NameRecord NameRecord;

        for (int i = 0; i < 5; i++) {
            pos = line.find(",");
            field = line.substr(0, pos);
            line.erase(0, pos + 1);
            switch (i) {
                case 0:
                    NameRecord.woj = field;
                    break;
                case 1:
                    NameRecord.voivodeship = field;
                    break;
                case 2:
                    NameRecord.secondName = field;
                    break;
                case 3:
                    NameRecord.gender = field;
                    break;
                case 4:
                    NameRecord.occurrences = stoi(field);
                    break;
            }
        }
        updateMostPopularNameAndQuantity(NameRecord);
        data.push_back(NameRecord);
    }

}

void NamesData::updateMostPopularNameAndQuantity(NameRecord nameRecord){
    unordered_map<string, int> totalNames;

    totalNames[nameRecord.secondName] += nameRecord.occurrences;
    if (totalNames[nameRecord.secondName] > mostPopularQuantity) {
        mostPopularQuantity = totalNames[nameRecord.secondName];
        mostPopularName = nameRecord.secondName;
    }
}

void NamesData::prepareStatisticsPerVoivodeship() {
    unordered_map<string, int> voivodeshipCounts;
    for (NameRecord& nameRecord : data) {
        if (voivodeshipCounts.find(nameRecord.voivodeship) == voivodeshipCounts.end()) {
            voivodeshipCounts[nameRecord.voivodeship] = nameRecord.occurrences;
        } else {
            voivodeshipCounts[nameRecord.voivodeship] += nameRecord.occurrences;
        }
    }

    data.clear();
    for (const auto& [voivodeship, occurrences] : voivodeshipCounts) {
        data.push_back({ "", voivodeship, "", "", occurrences });
    }
}

void NamesData::saveData(vector<NameRecord> data, string fileName) {
    ofstream file(fileName);
    for (NameRecord nameRecord : data) {
        file << nameRecord.voivodeship << ", " << nameRecord.occurrences << endl;
    }
}

vector<NameRecord> NamesData::getLoadedData() {
    return data;
}
