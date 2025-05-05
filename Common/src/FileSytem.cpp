#include "FileSytem.h"

std::vector<std::vector<std::string>> Reader::readEconomyCSV(const std::string& fileName)
{
	std::vector<std::vector<std::string>> data;
	std::ifstream file(fileName);
	ElementCount = 0; // Reset ElementCount for each read operation

	if (!file.is_open()) {
		std::cerr << "Erreur : impossible d'ouvrir le fichier " << fileName << std::endl;
		return data;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> elements;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) {
			elements.push_back(cell);
		}

		data.push_back(elements);
		ElementCount++;
		//printf("Nom: %s | Quantité: %s | Prix: %s\n", elements[0].c_str(), elements[1].c_str(), elements[2].c_str());
	}

	file.close();
	return data;
}

std::vector<SpriteDefinition> Reader::ReadAtlasMetaData(const std::string& csvPath)
{
	std::vector<SpriteDefinition> sprites;
	std::ifstream file(csvPath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + csvPath);
	}
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream lineStream(line);
		std::string cell;

		SpriteDefinition sprite;

		if (std::getline(lineStream, cell, ',')) sprite.filename = cell;
		if (std::getline(lineStream, cell, ',')) sprite.x = std::stoi(cell);
		if (std::getline(lineStream, cell, ',')) sprite.y = std::stoi(cell);
		if (std::getline(lineStream, cell, ',')) sprite.width = std::stoi(cell);
		if (std::getline(lineStream, cell, ',')) sprite.height = std::stoi(cell);
		sprites.push_back(sprite);
	}

	return sprites;
}
