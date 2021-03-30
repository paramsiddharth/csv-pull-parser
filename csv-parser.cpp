#include <iostream>
#include <fstream>
#include <string>
#include "csv-parser.hpp"

namespace CSVParser {
	class CSVReadStream {
		public:
		CSVReadStream(std::istream& stream) {
			std::string str;
			while (std::getline(stream, str)) {
				std::cout << str << ' ';
			};
			std::cout << std::endl;
		}
	};
}