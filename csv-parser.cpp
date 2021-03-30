#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "csv-parser.hpp"

CSVParser::CSVReadStream::CSVReadStream(std::string& filename) {
	this->stream = std::wifstream(filename);
	this->columns = CSVParser::tokenize(stream, this->eol);
	for (auto str: this->columns) {
		std::wcout << str << L' ';
	}
	std::wcout << std::endl;
}

CSVParser::CSVReadStream::~CSVReadStream() {
	this->stream.close();
}

std::vector<std::wstring> CSVParser::tokenize(std::wistream& stream, CSVParser::EOLSequence& eol) {
	std::vector<std::wstring> values;
	std::wstring currentToken = L"", line;
	wchar_t ch;
	int start = 0, pos = 0;
	bool inQuotes = false, lastTokenPushed = false;

	while (stream >> std::noskipws >> ch) {
		if (inQuotes) {
			if (ch == L'"') {
				auto p = stream.tellg();
				stream >> std::noskipws >> ch;
				if (ch == L'"') {
					currentToken += ch;
				} else {
					stream.seekg(p, std::ios_base::beg);
					values.push_back(currentToken);
					currentToken = L"";
				}
			}
		} else if (ch == L'"' && currentToken.size() == 0) {
			inQuotes = true;
		} else if (ch == L',') {
			values.push_back(currentToken);
			currentToken = L"";
		} else if (ch == L'\n') {
			if (eol == None)
				eol = LF;
			if (eol == LF) {
				values.push_back(currentToken);
				currentToken = L"";
				lastTokenPushed = true;
				break;
			} else {
				currentToken += ch;
			}
		} else if (ch == L'\r') {
			auto p = stream.tellg();
			stream >> std::noskipws >> ch;
			if (ch == L'\n') {
				if (eol == None)
					eol = CRLF;
				if (eol == CRLF) {
					values.push_back(currentToken);
					currentToken = L"";
					lastTokenPushed = true;
					break;
				} else {
					currentToken += L'\r';
					values.push_back(currentToken);
					currentToken = L"";
				}
				currentToken += ch;
			} else {
				stream.seekg(p, std::ios_base::beg);
				currentToken += L'\r';
			}
		} else {
			currentToken += ch;
		}
	}

	if (!lastTokenPushed)
		values.push_back(currentToken);

	return values;
}
