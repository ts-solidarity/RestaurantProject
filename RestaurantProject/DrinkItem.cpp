#include <iostream>
#include "DrinkItem.h"

DrinkItem::DrinkItem(int itemId, const std::string& itemName, double itemPrice)
	: MenuItem(itemId, itemName, itemPrice)
{
}

void DrinkItem::DisplayInfo() const
{
	std::cout << "Item Type: Drink" << std::endl;
	MenuItem::DisplayInfo();
}

void DrinkItem::ShowItem() const
{
	DisplayInfo();
}

double DrinkItem::CalculateDiscount() const
{
	// %10 discount on drink items
	return GetItemPrice() * 0.10;
}

MenuItem* DrinkItem::Clone() const
{
	return new DrinkItem(*this);
}

bool DrinkItem::IsDrink() const
{
	return true;
}

bool DrinkItem::IsFood() const
{
	return false;
}
