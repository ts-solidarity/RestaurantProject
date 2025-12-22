#pragma once
#include "Manager.h"
#include "Customer.h"
#include "Order.h"
#include "MenuItem.h"

class DeliveryPerson;

class Restaurant
{

public:

	Restaurant(const std::string& restaurantName);
	~Restaurant();

	std::string GetRestaurantName() const;
	Manager* GetManager() const;
	DeliveryPerson* GetAvailableDeliveryPerson() const;

	void SetRestaurantName(const std::string& restaurantName);
	void SetManager(Manager* manager);
	void SetDeliveryPeople(DeliveryPerson** deliveryPeople, int deliveryPeopleCount);

	void AddMenuItem(const MenuItem& menuItem);
	void DeleteMenuItem(const MenuItem& menuItem);
	
	void AddEmployee(DeliveryPerson* employee);
	void DeleteEmployee(DeliveryPerson* employee);

	Order* CreateOrder(Customer* customer);
	void DeleteOrder(Order* order);
	void RemoveOrder(Order* order);
	void AddItemToOrder(const MenuItem& item, Order* order);
	void DeleteItemFromOrder(const MenuItem& item, Order* order);
	Order* GetLatestOrder() const;
	Order* GetOrderByIndex(int index) const;

	void DisplayMenu() const;
	MenuItem* GetMenuItemById(int itemId) const;
	MenuItem* GetMenuItemByIndex(int itemIndex) const;

private:
	
	std::string m_RestaurantName;

	Manager* m_Manager;
	
	MenuItem** m_Menu;
	int m_MenuCount;
	
	Order** m_Orders;
	int m_OrderCount;
	
	DeliveryPerson** m_DeliveryPeople;
	int m_DeliveryPeopleCount;
};
