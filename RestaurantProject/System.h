#pragma once
#include <string>
#include "Restaurant.h"
#include "FoodItem.h"
#include "DrinkItem.h"


class System
{
	

public:

	System();
	~System();

	Restaurant* CreateRestaurant(const std::string& restaurantName, Manager* manager, DeliveryPerson** deliveryPeople, int deliveryPeopleCount);
	Manager* CreateManager(const std::string& userName, const std::string& userEmail, Restaurant* restaurant);
	DeliveryPerson* CreateDeliveryPerson(const std::string& userName, const std::string& userEmail, Restaurant* restaurant);
	Customer* CreateCustomer(const std::string& userName, const std::string& userEmail, const std::string& address);
	FoodItem* CreateFoodItem(const std::string& itemName, double itemPrice);
	DrinkItem* CreateDrinkItem(const std::string& itemName, double itemPrice);

	void RestaurantManager(Restaurant* restaurant, Manager* manager);
	void RestaurantDeliveryPerson(Restaurant* restaurant, DeliveryPerson* deliveryPerson);

	void AddRestaurant(Restaurant* restaurant);
	void DeleteRestaurant(Restaurant* restaurant);

	void AddCustomer(Customer* customer);
	void DeleteCustomer(Customer* customer);

	void BuildMarket();

private:

	int m_NextUserId = 1;
	int m_NextMenuItemId = 1;

	Restaurant** m_Restaurants;
	int m_RestaurantCount;

	Customer** m_Customers;
	int m_CustomerCount;


private:
	// constant values to produce different custom objects
	
	const std::string m_RestaurantNames[10] = {
		"Nusret",
		"HD Iskender",
		"Kofteci Yusuf",
		"La Pierre",
		"Klassje",
		"Harrier Du Bois",
		"Itoyia",
		"Katlempas",
		"Ekrem Doner",
		"ASPAVA"
	};

	const std::string m_Names[10] = {
		"Alice", 
		"Max",
		"Jack",
		"Jane",
		"Jasmin",
		"Angela",
		"John",
		"Trump",
		"Bismarck",
		"Macron"
	};

	const std::string m_Emails[4] = {
		"@gmail.com",
		"@yahoo.com",
		"@proton.me",
		"@ktu.edu.tr"
	};

	const std::string m_FoodNames[4] = {
		"Sushi",
		"Doner",
		"Kebap",
		"Iskender"
	};

	const std::string m_DrinkNames[4] = {
		"Ayran",
		"Cola",
		"Salgam",
		"Su"
	};

	const int m_FoodIds[4] = { 1, 2, 3, 4 };
	const int m_DrinkIds[4] = { 5, 6, 7, 8 };

};

