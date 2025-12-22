#include "System.h"
#include "DeliveryPerson.h"


System::System()
{
    m_Restaurants = nullptr;
    m_RestaurantCount = 0;
}

System::~System()
{
    // by design, system class owns only the restaurants
    // restaurants own everything else

    for (int i = 0; i < m_RestaurantCount; i++)
    {
		delete m_Restaurants[i];
    }

    delete[] m_Restaurants;
}

Restaurant* System::CreateRestaurant(const std::string& restaurantName, Manager* manager, DeliveryPerson** deliveryPeople, int deliveryPeopleCount)
{
    Restaurant* restaurant = new Restaurant{restaurantName};

	restaurant->SetDeliveryPeople(deliveryPeople, deliveryPeopleCount);
	return restaurant;
}

Manager* System::CreateManager(const std::string& userName, const std::string& userEmail, Restaurant* restaurant)
{
    return new Manager{ m_NextUserId++, userName, userEmail, restaurant };
}

DeliveryPerson* System::CreateDeliveryPerson(const std::string& userName, const std::string& userEmail, Restaurant* restaurant)
{
    return new DeliveryPerson{ m_NextUserId++, userName, userEmail, restaurant };
}

Customer* System::CreateCustomer(const std::string& userName, const std::string& userEmail, const std::string& address)
{
    return new Customer{ m_NextUserId++, userName, userEmail, address};
}

FoodItem* System::CreateFoodItem(const std::string& itemName, double itemPrice)
{
    return new FoodItem{ m_NextMenuItemId++, itemName, itemPrice };
}

DrinkItem* System::CreateDrinkItem(const std::string& itemName, double itemPrice)
{
    return new DrinkItem{ m_NextMenuItemId++, itemName, itemPrice};
}

void System::RestaurantManager(Restaurant* restaurant, Manager* manager)
{
    restaurant->SetManager(manager);
    manager->SetRestaurant(restaurant);
}

void System::RestaurantDeliveryPerson(Restaurant* restaurant, DeliveryPerson* deliveryPerson)
{
    restaurant->AddEmployee(deliveryPerson);
    deliveryPerson->SetRestaurant(restaurant);
}
