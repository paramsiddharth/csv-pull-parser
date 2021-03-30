#include <iostream>
#include <fstream>
#include "csv-parser.cpp"
using namespace std;
using namespace CSVParser;

int main() {
	// wfstream Fs("test.csv", std::fstream::in);

	string filename = "test.csv";
	CSVReadStream s(filename);

	// Fs.close();
}