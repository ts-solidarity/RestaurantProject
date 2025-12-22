#include <iostream>
#include "Manager.h"
#include "Restaurant.h"

Manager::Manager(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant)
	: Employee(userId, userName, userEmail, restaurant)
{

}

Manager::~Manager()
{

}

void Manager::DisplayInfo() const
{
	User::DisplayInfo();
	std::cout << "Affiliated restaurant: " << GetRestaurant()->GetRestaurantName() << std::endl;
	std::cout << "Status: Manager" << std::endl;
}

void Manager::HireDeliveryPerson(DeliveryPerson* employee)
{
	GetRestaurant()->AddEmployee(employee);
}

void Manager::FireDeliveryPerson(DeliveryPerson* employee)
{
	GetRestaurant()->DeleteEmployee(employee);
}

void Manager::AddMenuItem(const MenuItem& menuItem)
{
	GetRestaurant()->AddMenuItem(menuItem);
}

void Manager::DeleteMenuItem(const MenuItem& menuItem)
{
	GetRestaurant()->DeleteMenuItem(menuItem);
}
