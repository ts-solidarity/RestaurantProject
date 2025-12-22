#pragma once
#include "Employee.h"
#include "Order.h"


class DeliveryPerson : public Employee
{

public:
	
	DeliveryPerson(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant);
	~DeliveryPerson();
	
	void DisplayInfo() const override;
	
	Order* GetCurrentOrder() const;
	void SetCurrentOrder(Order* order);

	void CompleteCurrentOrder();
	bool IsOrderComplete() const override;

private:

	Order* m_CurrentOrder;

};
