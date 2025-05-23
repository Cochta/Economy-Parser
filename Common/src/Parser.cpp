#include "Parser.h"

void Parser::SortAlphabetically(bool isAscending)
{
	if (isAscending)
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Name > b.Name;
			});
	else
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Name < b.Name;
			});
}

void Parser::SortByQuantity(bool isAscending)
{
	if (isAscending)
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Quantity > b.Quantity;
			});
	else
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Quantity < b.Quantity;
			});
}

void Parser::SortByPrice(bool isAscending)
{
	if (isAscending)
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Price > b.Price;
			});
	else
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.Price < b.Price;
			});
}

void Parser::SortByRentability(bool isAscending)
{
	if (isAscending)
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.StackPrice > b.StackPrice;
			});
	else
		std::sort(AllItems.begin(), AllItems.end(), [](const Item& a, const Item& b) {
		return a.StackPrice < b.StackPrice;
			});
}

void Parser::Setup() {
	Reader reader;
	auto data = reader.readEconomyCSV("Ressource/Files/1.21.5_economy.csv");
	for (auto& row : data)
	{
		Item item;
		item.Id = row[0];
		item.ImagePath = row[1];
		item.Name = row[2];
		item.Quantity = std::stoi(row[3]);
		item.Price = std::stoi(row[4]);
		item.Parse();
		AllItems.push_back(item);
	}
	sprites = reader.ReadAtlasMetaData("Ressource/Files/1.21.5_atlas_metadata.csv");
}

void Item::Parse()
{
	StackPrice = (IsStackable ? STACK_SIZE : 1.f) / Quantity * Price;
	ShulkerPrice = SHULKER_SIZE * StackPrice;
	DCPrice = DC_SIZE * StackPrice;
}
