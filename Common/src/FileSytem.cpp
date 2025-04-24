#include "FileSytem.h"

std::vector<std::vector<std::string>> Reader::readCSV(const std::string& fileName)
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
