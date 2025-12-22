#pragma once
#include <string>


class MenuItem
{

public:

	MenuItem(int itemId, const std::string& itemName, double itemPrice);
	virtual ~MenuItem() = default;
	virtual void DisplayInfo() const;
	virtual void ShowItem() const = 0;
	virtual double CalculateDiscount() const = 0;
	virtual MenuItem* Clone() const = 0;
	virtual bool IsDrink() const = 0;
	virtual bool IsFood() const = 0;

	int GetItemId() const;
	std::string GetItemName() const;
	double GetItemPrice() const;

	void SetItemId(int itemId);
	void SetItemName(const std::string& itemName);
	void SetItemPrice(double itemPrice);


private:

	int m_ItemId;
	std::string m_ItemName;
	double m_ItemPrice;	

};
