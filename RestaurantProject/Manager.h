#pragma once
#include "Employee.h"
#include "MenuItem.h"

class DeliveryPerson;

class Manager : public Employee
{

public:

	Manager(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant);
	~Manager();

	void DisplayInfo() const override;

	void HireDeliveryPerson(DeliveryPerson* employee);
	void FireDeliveryPerson(DeliveryPerson* employee);

	void AddMenuItem(const MenuItem& menuItem);
	void DeleteMenuItem(const MenuItem& menuItem);


private:


};
