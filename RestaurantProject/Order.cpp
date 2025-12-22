#include <iostream>
#include "Order.h"
#include "Customer.h"
#include "DeliveryPerson.h"
#include "Restaurant.h"


Order::Order(Customer* customer, DeliveryPerson* deliveryPerson, Restaurant* restaurant)
{
	m_ItemCount = 0;
	m_OrderedItems = nullptr;
	m_Customer = customer;
	m_DeliveryPerson = deliveryPerson;
	m_Restaurant = restaurant;
	// to make order situations differ from each other, we use customer's name's length
	m_Situation = static_cast<Situation>(customer->GetUserName().length() % 3);
}

Order::~Order()
{
	for (int i = 0; i < m_ItemCount; i++)
	{
		delete m_OrderedItems[i];
	}

	delete[] m_OrderedItems;
}

MenuItem** Order::GetOrderedItems() const
{
	return m_OrderedItems;
}

int Order::GetItemCount() const
{
	return m_ItemCount;
}

void Order::AddItem(const MenuItem& item)
{
	int oldCount = m_ItemCount;
	int newCount = oldCount + 1;
	MenuItem** newOrderedItems = new MenuItem*[newCount];
	MenuItem* newItem = item.Clone();

	for (int i = 0; i < m_ItemCount; i++)
	{
		newOrderedItems[i] = m_OrderedItems[i];
	}

	newOrderedItems[newCount - 1] = newItem;
	delete[] m_OrderedItems;
	m_ItemCount = newCount;
	m_OrderedItems = newOrderedItems;
}

void Order::DeleteItem(const MenuItem& item)
{
	// if the order list is empty
	if (m_ItemCount == 0)
		return;

	// trying to detect the item
	int index = -1;

	for (int i = 0; i < m_ItemCount; i++)
	{
		if (item.GetItemId() == m_OrderedItems[i]->GetItemId())
		{
			index = i;
			break;
		}
	}

	// if item is not found we do nothing
	if (index == -1)
		return;

	// now we are sure there is a matched item so we delete it first
	delete m_OrderedItems[index];

	// if the array was only one element, we don't need to assign items again since it's empty now
	if (m_ItemCount - 1 == 0)
	{
		delete[] m_OrderedItems;
		m_OrderedItems = nullptr;
		m_ItemCount = 0;
		return;
	}
	
	// if there are still elements left, we will copy them except the deleted one
	MenuItem** newOrderedItems = new MenuItem*[m_ItemCount - 1];

	for (int i = 0, j = 0; i < m_ItemCount - 1; i++)
	{
		if (j == index)
		{
			j += 1;
		}

		newOrderedItems[i] = m_OrderedItems[j];
		j++;
	}

	delete[] m_OrderedItems;
	m_OrderedItems = newOrderedItems;
	m_ItemCount -= 1;
}

void Order::SetCustomer(Customer* customer)
{
	m_Customer = customer;
}

void Order::SetDeliveryPerson(DeliveryPerson* deliveryPerson)
{
	m_DeliveryPerson = deliveryPerson;
}

void Order::SetRestaurant(Restaurant* restaurant)
{
	m_Restaurant = restaurant;
}

void Order::SetSituation(Order::Situation situation)
{
	m_Situation = situation;
}

std::string Order::GetSituationString() const
{
	std::string situation = "";

	if (m_Situation == Situation::Preparing)
		situation = "Preparing";
	else if (m_Situation == Situation::OnTheWay)
		situation = "On the way";
	else
		situation = "Delivered";

	return situation;
}

Customer* Order::GetCustomer() const
{
	return m_Customer;
}

DeliveryPerson* Order::GetDeliveryPerson() const
{
	return m_DeliveryPerson;
}

Restaurant* Order::GetRestaurant() const
{
	return m_Restaurant;
}

Order::Situation Order::GetSituation() const
{
	return m_Situation;
}

void Order::DisplayInfo() const
{
	std::cout << "**************************************" << std::endl;
	std::cout << "Order Information:" << std::endl;
	std::cout << "Customer name: " << m_Customer->GetUserName() << std::endl;
	std::cout << "Delivery person name: " << m_DeliveryPerson->GetUserName() << std::endl;
	std::cout << "Order items:" << std::endl;

	for (int i = 0; i < m_ItemCount; i++)
	{
		m_OrderedItems[i]->DisplayInfo();
	}

	std::cout << "Total price before discount: " << CalculateTotalPrice() << std::endl;
	std::cout << "Total discount: " << CalculateTotalDiscount() << std::endl;
	std::cout << "Final price: " << FinalPrice() << std::endl;
	std::cout << "Order situation: " << GetSituationString() << std::endl;
	std::cout << "**************************************" << std::endl;
}

double Order::CalculateTotalPrice() const
{
	double totalPrice = 0.0;

	for (int i = 0; i < m_ItemCount; i++)
	{
		totalPrice += m_OrderedItems[i]->GetItemPrice();
	}

	return totalPrice;
}

double Order::CalculateTotalDiscount() const
{
	double totalDiscount = 0.0;

	for (int i = 0; i < m_ItemCount; i++)
	{
		totalDiscount += m_OrderedItems[i]->CalculateDiscount();
	}

	return totalDiscount;
}

double Order::FinalPrice() const
{
	double finalPrice = CalculateTotalPrice() - CalculateTotalDiscount();
	return finalPrice;
}
