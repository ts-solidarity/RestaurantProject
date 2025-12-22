#include "Restaurant.h"
#include "FoodItem.h"
#include "DrinkItem.h"
#include "DeliveryPerson.h"


Restaurant::Restaurant(const std::string& restaurantName)
{
    m_RestaurantName = restaurantName;

    m_Manager = nullptr;

    m_Menu = nullptr;
    m_MenuCount = 0;

    m_Orders = nullptr;
    m_OrderCount = 0;

    m_DeliveryPeople = nullptr;
    m_DeliveryPeopleCount = 0;
}

Restaurant::~Restaurant()
{
    // restaurant owns menu items, employees and orders by design
    // so it's got to delete every one of them when destroying itself to prevent memory leaks

    for (int i = 0; i < m_MenuCount; i++)
    {
        delete m_Menu[i];
    }

    delete[] m_Menu;

    for (int i = 0; i < m_DeliveryPeopleCount; i++)
    {
        delete m_DeliveryPeople[i];
    }
    
    delete[] m_DeliveryPeople;

    for (int i = 0; i < m_OrderCount; i++)
    {
        delete m_Orders[i];
    }

    delete[] m_Orders;
}

void Restaurant::AddMenuItem(const MenuItem& menuItem)
{
    // checking if the same type of item is already on the menu
    // if so, we will return without doing anything
    for (int i = 0; i < m_MenuCount; i++)
    {
        if (menuItem.GetItemId() == m_Menu[i]->GetItemId())
            return;
    }

    // if menuItem is a new type of item, we want to update our menu

    // we start by creating a new array, with one more space compared to current menu
    MenuItem** newMenu = new MenuItem* [m_MenuCount + 1];

    // we copy everything in the old menu to the new menu
    for (int i = 0; i < m_MenuCount; i++)
    {
        newMenu[i] = m_Menu[i];
    }

    // the only thing left to do is to add the new item at the end of the list
    MenuItem* newMenuItem = menuItem.Clone();
    newMenu[m_MenuCount] = newMenuItem;

    // now update and done
    m_MenuCount++;
    delete[] m_Menu;
    m_Menu = newMenu;
}

void Restaurant::DeleteMenuItem(const MenuItem& menuItem)
{
    if (m_MenuCount == 0)
    {
        return;
    }

    int index = -1;

    for (int i = 0; i < m_MenuCount; i++)
    {
        if (m_Menu[i]->GetItemId() == menuItem.GetItemId())
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return;
    }

    MenuItem** newMenu = new MenuItem * [m_MenuCount - 1];

    for (int i = 0, j = 0; i < m_MenuCount - 1; i++)
    {
        if (j == index)
        {
            j++;
        }

        newMenu[i] = m_Menu[j];
        j++;
    }

    delete[] m_Menu;
    m_MenuCount--;
    m_Menu = newMenu;
}

void Restaurant::AddEmployee(DeliveryPerson* employee)
{
    for (int i = 0; i < m_DeliveryPeopleCount; i++)
    {
        if (employee == m_DeliveryPeople[i])
            return;
    }

    DeliveryPerson** newEmployees = new DeliveryPerson * [m_DeliveryPeopleCount + 1];

    for (int i = 0; i < m_DeliveryPeopleCount; i++)
    {
        newEmployees[i] = m_DeliveryPeople[i];
    }
    
    newEmployees[m_DeliveryPeopleCount] = employee;

    m_DeliveryPeopleCount++;
    delete[] m_DeliveryPeople;
    m_DeliveryPeople = newEmployees;
}

void Restaurant::DeleteEmployee(DeliveryPerson* employee)
{
    if (m_DeliveryPeopleCount == 0)
    {
        return;
    }

    int index = -1;

    for (int i = 0; i < m_DeliveryPeopleCount; i++)
    {
        if (m_DeliveryPeople[i] == employee)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        return;
    }

    DeliveryPerson** newEmployees = new DeliveryPerson * [m_DeliveryPeopleCount - 1];

    for (int i = 0, j = 0; i < m_DeliveryPeopleCount - 1; i++)
    {
        if (j == index)
        {
            j++;
        }

        newEmployees[i] = m_DeliveryPeople[j];
        j++;
    }

    delete[] m_DeliveryPeople;
    m_DeliveryPeopleCount--;
    m_DeliveryPeople = newEmployees;
}

Order* Restaurant::AddOrder(Customer* customer, DeliveryPerson* deliveryPerson)
{
    Order* newOrder = new Order{customer, deliveryPerson, this};
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

void Restaurant::DeleteOrder(Order* order)
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
    delete order;
}

void Restaurant::RemoveOrder(Order* order)
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
}

Order* Restaurant::GetLatestOrder() const
{
    if (m_OrderCount == 0)
        return nullptr;
    return m_Orders[m_OrderCount - 1];
}

Order* Restaurant::GetOrderByIndex(int index) const
{
    if (index > m_OrderCount - 1)
        return nullptr;
    return m_Orders[index];
}

void Restaurant::AddItemToOrder(const MenuItem& item, Order* order)
{
    order->AddItem(item);
}

void Restaurant::DeleteItemFromOrder(const MenuItem& item, Order* order)
{
    order->DeleteItem(item);
}

std::string Restaurant::GetRestaurantName() const
{
    return m_RestaurantName;
}

Manager* Restaurant::GetManager() const
{
    return m_Manager;
}

DeliveryPerson* Restaurant::GetAvailableDeliveryPerson() const
{
    DeliveryPerson* deliveryPerson = nullptr;

    for (int i = 0; i < m_DeliveryPeopleCount; i++)
    {
        if (m_DeliveryPeople[i]->IsOrderComplete())
        {
            deliveryPerson = m_DeliveryPeople[i];
        }
    }

    return deliveryPerson;
}

void Restaurant::SetRestaurantName(const std::string& restaurantName)
{
    m_RestaurantName = restaurantName;
}

void Restaurant::SetManager(Manager* manager)
{
    m_Manager = manager;
}
