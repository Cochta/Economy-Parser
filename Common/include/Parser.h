#pragma once

#include "FileSytem.h"
#include "Metrics.h"

struct Item
{
	std::string Id;
	std::string ImagePath;
	std::string Name;
	int Quantity = 0;
	int Price = 0;
	bool isStackable = true;

};

struct Parser
{
	std::vector<std::vector<std::string>> Data;
	void Setup();
};