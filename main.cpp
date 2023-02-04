#include <iostream>
#include <string>
#include <vector>
#include "NamesData.h"
#include "NamesData.cpp"

using namespace std;

void visualizeData(vector<NameRecord> data) {
    ofstream file;

    file.open("wykres.html");

    file << "<!DOCTYPE html>" << endl;
    file << "<meta charset='UTF-8'>" << endl;
    file << "<html>" << endl;
    file << "<head>" << endl;
    file << "<script src = \"https://cdn.jsdelivr.net/npm/chart.js@2.9.3/dist/Chart.min.js\"></script>" << endl;
    file << "</head>" << endl;
    file << "<body>" << endl;
    file << "<canvas id = \"myChart\"></canvas>" << endl;
    file << "<script>" << endl;
    file << "var ctx = document.getElementById('myChart').getContext('2d');" << endl;
    file << "var myChart = new Chart(ctx, {" << endl;
    file << "type: 'bar'," << endl;
    file << "data: {" << endl;
    file << "labels: [";
    for (NameRecord nameRecord : data) {
        file << "'" << (nameRecord.voivodeship) << "',";
    }
    file << "]," << endl;
    file << "datasets: [{" << endl;
    file << "label: 'Całkowita liczba nadanych drugich imion w województwie'," << endl;
    file << "data: [";
    for (NameRecord nameRecord : data) {
        file << nameRecord.occurrences << ",";
    }
    file << "]," << endl;
    file << "backgroundColor: [" << endl;
    for (int i = 0; i < data.size(); i++) {
        file << "'rgba(255, 99, 132, 0.2)'," << endl;
    }
    file << "]," << endl;
    file << "borderColor: [" << endl;
    for (int i = 0; i < data.size(); i++) {
        file << "'rgba(255, 99, 132, 1)'," << endl;
    }
    file << "]," << endl;
    file << "borderWidth: 1" << endl;
    file << "}]" << endl;
    file << "}," << endl;
    file << "options: {" << endl;
    file << "scales: {" << endl;
    file << "y: {" << endl;
    file << "beginAtZero: true" << endl;
    file << "}" << endl;
    file << "}" << endl;
    file << "}" << endl;
    file << "});" << endl;
    file << "</script>" << endl;
    file << "</body>" << endl;
    file << "</html>" << endl;
    file.close();
}

int main(int argc, char* argv[]) {
    NamesData namesData;

    for (int i = 1; i < argc; i++) {
        string fileName = argv[i];
        namesData.appendDataFromFile(fileName);
    }

    cout << namesData.getLoadedData().size() << endl;

    namesData.prepareStatisticsPerVoivodeship();

    for (NameRecord record : namesData.getLoadedData()) {
        cout << record.voivodeship << " " << record.occurrences << endl;
    }

    visualizeData(namesData.getLoadedData());
    string outputFileName = "processed_name_data.csv";
    namesData.saveData(namesData.getLoadedData(), outputFileName);
    return 0;
}
