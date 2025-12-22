#include <iostream>
#include "FoodItem.h"

FoodItem::FoodItem(int itemId, const std::string& itemName, double itemPrice)
	: MenuItem(itemId, itemName, itemPrice)
{
}

void FoodItem::DisplayInfo() const
{
	std::cout << "Item Type: Food" << std::endl;
	MenuItem::DisplayInfo();
}

void FoodItem::ShowItem() const
{
	DisplayInfo();
}

double FoodItem::CalculateDiscount() const
{
	// %5 discount on food items
	return GetItemPrice() * 0.05;
}

MenuItem* FoodItem::Clone() const
{
	return new FoodItem(*this);
}

bool FoodItem::IsDrink() const
{
	return false;
}

bool FoodItem::IsFood() const
{
	return true;
}
