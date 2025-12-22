#pragma once
#include "User.h"

class Restaurant;

class Employee : public User
{

public:
	
	Employee(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant);
	~Employee();
	
	virtual void DisplayInfo() const override = 0;
	
	Restaurant* GetRestaurant() const;
	void SetRestaurant(Restaurant* restaurant);

	virtual bool IsOrderComplete() const = 0;

private:

	Restaurant* m_Restaurant;

};
