#include <iostream>
#include <fstream>
#include "csv-parser.cpp"
using namespace std;
using namespace CSVParser;

int main() {
	ifstream Fs("test.csv");

	CSVReadStream s(Fs);

	Fs.close();
}