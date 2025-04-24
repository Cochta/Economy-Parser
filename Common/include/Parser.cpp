#include "Parser.h"

void Parser::Setup()
{
	Reader reader;
	Data = reader.readCSV("Release/Data/1.21.5.csv");

	//Loader loader;
	//for (const auto& row : data) {
	//	if (row.size() >= 5) {
	//		std::string itemId = row[0];
	//		std::string imagePath = row[1];
	//		std::string name = row[2];
	//		std::string quantity = row[3];
	//		std::string price = row[4];
	//		// Load the image using the Loader class
	//		Data.push_back({itemId,imagePath,name,quantity,price});
	//		printf("%s\n", name);
	//		printf("%s\n", imagePath);
	//		printf("%s\n", quantity);
	//		printf("%s\n", price);

	//	}
	//}
}
