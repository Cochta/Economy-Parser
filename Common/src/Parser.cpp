#include "Parser.h"

void Parser::Setup() {
	Reader reader;
	Data = reader.readCSV("Release/data/1.21.5.csv");
}