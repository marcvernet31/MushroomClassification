#include <iostream>
#include <vector>
#include <string>

// pels fitxers:
#include <fstream> // file stream
#include <sstream> // string stream

using namespace std;

using Matrix = vector< vector<double> >;
using Table = vector< vector<char> >;
/** FUNCIONS PER LLEGIR I ESCRIURE */

Table read_csv(string fileName) {
    fstream dataFile;
    dataFile.open(fileName);
    Table data;
    string row;
    while (getline(dataFile, row)) {
        vector<char> dataRow;
        for (char c: row) {
            if (c != ',') {
                dataRow.push_back(c);
            }
        }
        data.push_back(dataRow);
    }
    dataFile.close();
    return data;
}

/** writes the information from the matrix output to the output file (fileName) */
void writeOut(string& fileName, const Matrix& output, int s) {
    fstream fileOut;
    fileOut.open(fileName);
    int k = 0;
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            fileOut << output[i][j];
            if (j != s-1) {
                fileOut << ", ";
            }
            else ++k;
        }
        fileOut << endl;
    }
    fileOut.close();
    cout << k << endl;
}

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- //
/** FUNCIONS PER CALCULAR */
double obsDist(const vector<char>& a, const vector<char>& b) {
    // assert(a.size()==b.size)
    int n = a.size();
    double dist = 0;
    for (int k = 1; k < n; ++k) {
        if (a[k] != b[k]) {
            ++dist;
        }
    }
    return dist; // dist / n
}

// calcula la matriu de distàncies deixant els valors a distances prenent les dades de data.
void calcDistMatrix(Matrix& distances, const Table& data, int s) {
    for (int i = 0; i < s; ++i) {
        for (int j = i; j < s; ++j) {
            double d = 0;
            if (i != j) {
                d = obsDist(data[i], data[j]);
            }
            distances[i][j] = d;
            distances[j][i] = d;
        }
    }
}

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- //
int main() {
    string fileInput;
    string fileOutput;

    // per entrar com a parametre:
    cout << "Enter input file name: ";
    cin >> fileInput;
    cout << endl;
    cout << "Enter output file name: ";
    cin >> fileOutput;
    cout << endl;

    Table bolets = read_csv(fileInput);

    int N = bolets.size(); // 8124
    cout << N << endl;
    Matrix distances(N, vector<double>(N, 0));

    calcDistMatrix(distances, bolets, N);
    cout << distances.size() << ", " << distances[1].size() << endl;

    // write out the result
    writeOut(fileOutput, distances, N);
}
