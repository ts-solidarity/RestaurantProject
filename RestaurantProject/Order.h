#pragma once
#include "MenuItem.h"

class Customer;
class DeliveryPerson;
class Restaurant;

class Order
{

public:

	enum class Situation
	{
		Preparing = 0, OnTheWay, Delivered
	};

public:

	Order(Customer* customer, DeliveryPerson* deliveryPerson, Restaurant* restaurant);
	~Order();

	MenuItem** GetOrderedItems() const;
	int GetItemCount() const;

	void AddItem(const MenuItem& item);
	void DeleteItem(const MenuItem& item);

	void SetCustomer(Customer* customer);
	void SetDeliveryPerson(DeliveryPerson* deliveryPerson);
	void SetRestaurant(Restaurant* restaurant);
	void SetSituation(Order::Situation situation);
	std::string GetSituationString() const;

	Customer* GetCustomer() const;
	DeliveryPerson* GetDeliveryPerson() const;
	Restaurant* GetRestaurant() const;
	Order::Situation GetSituation() const;

	void DisplayInfo() const;
	double CalculateTotalPrice() const;
	double CalculateTotalDiscount() const;
	double FinalPrice() const;

	// disabling copy with op overloading
	Order(const Order&) = delete;
	Order& operator=(const Order&) = delete;


private:

	MenuItem** m_OrderedItems;
	int m_ItemCount;
	Customer* m_Customer;
	DeliveryPerson* m_DeliveryPerson;
	Restaurant* m_Restaurant;
	Situation m_Situation;
};
