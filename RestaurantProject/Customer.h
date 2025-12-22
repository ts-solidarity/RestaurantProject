#pragma once
#include "User.h"
#include "Order.h"

class Restaurant;


class Customer : public User
{

public:

	Customer(int userId, const std::string& userName, const std::string& userEmail, const std::string& address);
	~Customer();

	Order* CreateOrder(Restaurant* restaurant);
	void RemoveOrder(Order* order);
	Order* GetLatestOrder() const;
	Order* GetOrderByIndex(int index) const;
	void AddItemToOrder(const MenuItem& item, Order* order);
	void DeleteItemFromOrder(const MenuItem& item, Order* order);

	std::string GetAddress() const;
	void SetAddress(const std::string& address);


private:

	Order** m_Orders;
	int m_OrderCount;

	std::string m_Address;

};
