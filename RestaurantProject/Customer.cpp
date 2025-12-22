#include "Restaurant.h"
#include "Customer.h"

Customer::Customer(int userId, const std::string& userName, const std::string& userEmail, const std::string& address)
    : User(userId, userName, userEmail)
{
    m_Orders = nullptr;
    m_OrderCount = 0;
    m_Address = address;
}

Customer::~Customer()
{
    delete[] m_Orders;
}

Order* Customer::CreateOrder(Restaurant* restaurant)
{
    Order* newOrder = restaurant->CreateOrder(this);
    Order** newOrders = new Order * [m_OrderCount + 1];

    for (int i = 0; i < m_OrderCount; i++)
    {
        newOrders[i] = m_Orders[i];
    }

    newOrders[m_OrderCount] = newOrder;
    delete[] m_Orders;
    m_OrderCount++;
    m_Orders = newOrders;
    return newOrder;
}

void Customer::RemoveOrder(Order* order)
{
    if (m_OrderCount == 0)
    {
        return;
    }

    int index = -1;

    for (int i = 0; i < m_OrderCount; i++)
    {
        if (m_Orders[i] == order)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return;
    }

    Order** newOrders = new Order * [m_OrderCount - 1];

    for (int i = 0, j = 0; i < m_OrderCount - 1; i++)
    {
        if (j == index)
        {
            j++;
        }

        newOrders[i] = m_Orders[j];
        j++;
    }

    delete[] m_Orders;
    m_OrderCount--;
    m_Orders = newOrders;
    order->GetRestaurant()->DeleteOrder(order);
}

Order* Customer::GetLatestOrder() const
{
    if (m_OrderCount == 0)
        return nullptr;
    return m_Orders[m_OrderCount - 1];
}

Order* Customer::GetOrderByIndex(int index) const
{
    if (index > m_OrderCount - 1)
        return nullptr;
    return m_Orders[index];
}

void Customer::AddItemToOrder(const MenuItem& item, Order* order)
{
    order->AddItem(item);
}

void Customer::DeleteItemFromOrder(const MenuItem& item, Order* order)
{
    order->DeleteItem(item);
}

std::string Customer::GetAddress() const
{
    return m_Address;
}

void Customer::SetAddress(const std::string& address)
{
    m_Address = address;
}

