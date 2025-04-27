#pragma once

#include "FileSytem.h"
#include "Metrics.h"
#include <algorithm>
using namespace Metrics;

struct Item
{
	std::string Id;
	std::string ImagePath;
	std::string Name;
	int Quantity = 0;
	int Price = 0;
	bool IsStackable = true;
	float StackPrice = 0;
	float ShulkerPrice = 0;
	float DCPrice = 0;


	bool IsValid() const
	{
		return !Id.empty() && !ImagePath.empty() && !Name.empty() && Quantity > 0 && Price > 0;
	}
	void Parse();

};

struct Parser
{
	char SearchText[128] = "";
	std::vector<Item> AllItems;

	void SortAlphabetically(bool isAscending = true);
	void SortByPrice(bool isAscending = true);
	void SortByQuantity(bool isAscending = true);
	void SortByRentability(bool isAscending = true);

	void Setup();

	void TearDown();
};