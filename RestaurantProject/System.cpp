#include "System.h"
#include "DeliveryPerson.h"


System::System()
{
    m_Restaurants = nullptr;
    m_RestaurantCount = 0;

	m_Customers = nullptr;
	m_CustomerCount = 0;
}

System::~System()
{
	// by design, system class owns all customers and restaurants
    // everything else is owned by restaurants

    // deleting restaurants
    for (int i = 0; i < m_RestaurantCount; i++)
    {
		delete m_Restaurants[i];
    }

    delete[] m_Restaurants;


    // deleting customers
    for (int i = 0; i < m_CustomerCount; i++)
    {
		delete m_Customers[i]; 
    }

	delete[] m_Customers;
}

Restaurant* System::CreateRestaurant(const std::string& restaurantName, Manager* manager, DeliveryPerson** deliveryPeople, int deliveryPeopleCount)
{
    Restaurant* restaurant = new Restaurant{restaurantName};
	restaurant->SetDeliveryPeople(deliveryPeople, deliveryPeopleCount);
    AddRestaurant(restaurant);
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
    Customer* customer = new Customer{ m_NextUserId++, userName, userEmail, address};
	AddCustomer(customer);
    return customer;
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

void System::AddRestaurant(Restaurant* restaurant)
{
    if (restaurant == nullptr)
        return;

    for (int i = 0; i < m_RestaurantCount; i++)
    {
        if (m_Restaurants[i] == restaurant)
            return;
    }

    Restaurant** newRestaurants = new Restaurant * [m_RestaurantCount + 1];

    for (int i = 0; i < m_RestaurantCount; i++)
    {
        newRestaurants[i] = m_Restaurants[i];
    }

    newRestaurants[m_RestaurantCount] = restaurant;
    m_RestaurantCount++;
    delete[] m_Restaurants;
    m_Restaurants = newRestaurants;
}

void System::DeleteRestaurant(Restaurant* restaurant)
{
    if (restaurant == nullptr || m_RestaurantCount <= 0)
        return;

    int index = -1;

    for (int i = 0; i < m_RestaurantCount; i++)
    {
        if (m_Restaurants[i] == restaurant)
            index = i;
    }

    if (index == -1)
        return;

    Restaurant** newRestaurants = new Restaurant * [m_RestaurantCount - 1];

    for (int i = 0, j = 0; i < m_RestaurantCount - 1; i++)
    {
        if (j == index)
            j++;

        newRestaurants[i] = m_Restaurants[j++];
    }

    m_RestaurantCount--;
    delete[] m_Restaurants;
    m_Restaurants = newRestaurants;
}

void System::AddCustomer(Customer* customer)
{
    if (customer == nullptr)
		return;

	for (int i = 0; i < m_CustomerCount; i++)
    {
        if (m_Customers[i] == customer)
            return;
	}

	Customer** newCustomers = new Customer * [m_CustomerCount + 1];
    
    for (int i = 0; i < m_CustomerCount; i++)
    {
        newCustomers[i] = m_Customers[i];
	}

    newCustomers[m_CustomerCount] = customer;
    m_CustomerCount++;
    delete[] m_Customers;
	m_Customers = newCustomers;
}

void System::DeleteCustomer(Customer* customer)
{
    if (customer == nullptr || m_CustomerCount <= 0)
        return;

    int index = -1;

    for (int i = 0; i < m_CustomerCount; i++)
    {
        if (m_Customers[i] == customer)
            index = i;
    }

    if (index == -1)
        return;

    Customer** newCustomers = new Customer * [m_CustomerCount - 1];

    for (int i = 0, j = 0; i < m_CustomerCount - 1; i++)
    {
        if (j == index)
            j++;
        newCustomers[i] = m_Customers[j++];
    }

    m_CustomerCount--;
    delete[] m_Customers;
	m_Customers = newCustomers;
}

void System::BuildMarket()
{
    // preset values
    int restaurantCount = 10;
    int managerCount = restaurantCount;
    int deliveryPersonCountPerRestaurant = 3;
    int customerCount = 100;

	// before all of that, we need to create menu items
	DrinkItem** drinkItems = new DrinkItem * [4];
	FoodItem** foodItems = new FoodItem * [4];

    for (int i = 0; i < 4; i++)
    {
        foodItems[i] = CreateFoodItem(m_FoodNames[i], 10.0 + i * 5);
        drinkItems[i] = CreateDrinkItem(m_DrinkNames[i], 3.0 + i * 1.5);
	}

	// creating restaurants with managers and delivery persons
    for (int i = 0; i < restaurantCount; i++)
    {
        // first, we create the manager
        std::string managerName = m_Names[i % 10];
        std::string managerEmail = managerName + std::to_string(m_NextUserId) + m_Emails[i % 4];

        Manager* manager = CreateManager(managerName, managerEmail, nullptr);

        // second, we need to create deliverymen
        DeliveryPerson** deliveryPeople = new DeliveryPerson * [deliveryPersonCountPerRestaurant];

        for (int j = 0; j < deliveryPersonCountPerRestaurant; j++)
        {
            std::string name = m_Names[j % 10];
            std::string email = name + std::to_string(m_NextUserId) + m_Emails[i % 4];
            deliveryPeople[j] = CreateDeliveryPerson(name, email, nullptr);
        }

        // now we can create the restaurant
        Restaurant* restaurant = CreateRestaurant(m_RestaurantNames[i], manager, deliveryPeople, deliveryPersonCountPerRestaurant);

        // last, we gotta put some items on the menu
        for (int k = 0; k < 4; k++)
        {
            restaurant->AddMenuItem(*foodItems[k]);
            restaurant->AddMenuItem(*drinkItems[k]);
		}
    }

    // deleting above items to prevent memoryleak
    for (int i = 0; i < 4; i++)
    {
		delete drinkItems[i];
        delete foodItems[i];
    }

    delete[] drinkItems;
	delete[] foodItems;

    // now we can create customers
    for (int i = 0; i < customerCount; i++)
    {
        CreateCustomer(
            m_Names[i % 10],
            m_Names[i % 10] + std::to_string(m_NextUserId) + m_Emails[i % 4],
            "Address_" + std::to_string(i + 1));
    }

	// finally, it is time to add some orders for customers
    for (int i = 0; i < m_CustomerCount; i++)
    {
		Customer* customer = m_Customers[i];
		Restaurant* restaurant = m_Restaurants[i % m_RestaurantCount];
		Order* order = customer->CreateOrder(restaurant);
		MenuItem* item1 = restaurant->GetMenuItemByIndex(i % restaurant->GetMenuItemByIndex(0)->GetItemId());
		MenuItem* item2 = restaurant->GetMenuItemByIndex((i + 1) % restaurant->GetMenuItemByIndex(0)->GetItemId());
        customer->AddItemToOrder(*item1, order);
		customer->AddItemToOrder(*item2, order);
    }
}
