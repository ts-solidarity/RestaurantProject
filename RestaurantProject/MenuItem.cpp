#include <iostream>
#include "MenuItem.h"

MenuItem::MenuItem(int itemId, const std::string& itemName, double itemPrice)
{
	m_ItemId = itemId;
	m_ItemName = itemName;
	m_ItemPrice = itemPrice;
}

void MenuItem::DisplayInfo() const
{
	std::cout << "Item ID: " << m_ItemId << std::endl;
	std::cout << "Item name: " << m_ItemName << std::endl;
	std::cout << "Item price: " << m_ItemPrice << std::endl;
	std::cout << "Item price (discount applied)" << m_ItemPrice - CalculateDiscount() << std::endl;
}

int MenuItem::GetItemId() const
{
	return m_ItemId;
}

std::string MenuItem::GetItemName() const
{
	return m_ItemName;
}

double MenuItem::GetItemPrice() const
{
	return m_ItemPrice;
}

void MenuItem::SetItemId(int itemId)
{
	m_ItemId = itemId;
}

void MenuItem::SetItemName(const std::string& itemName)
{
	m_ItemName = itemName;
}

void MenuItem::SetItemPrice(double itemPrice)
{
	m_ItemPrice = itemPrice;
}
