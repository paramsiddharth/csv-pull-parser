#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace CSVParser {
	class CSVReadStream;
	class CSVWriteStream;

	const std::string WHITESPACE = " \n\r\t\f\v";
	
	enum Error {
		NoError = 0,
		InvalidColumns
	};
	enum EOLSequence {
		None = 0,
		LF,
		CRLF
	};

	class CSVReadStream {
		private:
		std::vector<std::wstring> columns;
		enum Error err = NoError;
		enum EOLSequence eol = None;
		std::wifstream stream;

		public:
		CSVReadStream(std::string&);
		virtual ~CSVReadStream();
	};

	std::vector<std::wstring> tokenize(std::wistream&, CSVParser::EOLSequence&);
}