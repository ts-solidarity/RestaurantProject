#include <iostream>
#include "DeliveryPerson.h"

DeliveryPerson::DeliveryPerson(int userId, const std::string& userName, const std::string& userEmail, Restaurant* restaurant)
	: Employee(userId, userName, userEmail, restaurant)
{
	m_CurrentOrder = nullptr;
}

DeliveryPerson::~DeliveryPerson()
{

}

void DeliveryPerson::DisplayInfo() const
{

}

Order* DeliveryPerson::GetCurrentOrder() const
{
	return m_CurrentOrder;
}

void DeliveryPerson::SetCurrentOrder(Order* order)
{
	m_CurrentOrder = order;
}

void DeliveryPerson::CompleteCurrentOrder()
{
	if (m_CurrentOrder == nullptr)
		return;

	m_CurrentOrder->SetSituation(Order::Situation::Delivered);
	m_CurrentOrder = nullptr;
}

bool DeliveryPerson::IsOrderComplete() const
{
	if (m_CurrentOrder == nullptr)
		return true;

	return m_CurrentOrder->GetSituation() == Order::Situation::Delivered;
}
