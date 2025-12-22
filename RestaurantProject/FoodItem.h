#pragma once
#include "MenuItem.h"


class FoodItem : public MenuItem
{

public:

	FoodItem(int itemId, const std::string& itemName, double itemPrice);
	void DisplayInfo() const override;
	void ShowItem() const override;
	double CalculateDiscount() const override;
	MenuItem* Clone() const override;
	bool IsDrink() const override;
	bool IsFood() const override;

private:



};

