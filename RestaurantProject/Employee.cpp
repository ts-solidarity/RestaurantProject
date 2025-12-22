#include "Employee.h"
#include "Restaurant.h"

Employee::Employee(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant)
	: User(userId, userName, userEmail)
{
	m_Restaurant = restaurant;
}

Employee::~Employee()
{

}

Restaurant* Employee::GetRestaurant() const
{
	return m_Restaurant;
}

void Employee::SetRestaurant(Restaurant* restaurant)
{
	m_Restaurant = restaurant;
}

bool Employee::IsOrderComplete() const
{
	return false;
}

