#include "Parser.h"

void Parser::Setup() {
	Reader reader;
	auto data = reader.readCSV("Release/data/1.21.5.csv");
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
}

void Item::Parse()
{
	StackPrice = (IsStackable ? STACK_SIZE : 1.f) / Quantity * Price;
	ShulkerPrice = SHULKER_SIZE * StackPrice;
	DCPrice = DC_SIZE * StackPrice;
}
