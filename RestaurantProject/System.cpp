#include <iostream>
#include <iomanip>
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
	restaurant->SetManager(manager);
	manager->SetRestaurant(restaurant);
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

void System::Run()
{
	int choice = -1;

	while (choice != 0)
	{
		std::cout << "\n" << std::setw(50) << std::setfill('=') << "" << std::endl;
		std::cout << std::setfill(' ') << std::setw(35) << std::right << "RESTAURANT MANAGEMENT SYSTEM" << std::endl;
		std::cout << std::setw(50) << std::setfill('=') << "" << std::setfill(' ') << std::endl;
		std::cout << " 1. [List] All Restaurants" << std::endl;
		std::cout << " 2. [View] Restaurant Menu" << std::endl;
		std::cout << " 3. [Order] Create New Order" << std::endl;
		std::cout << " 4. [Status] View Order Status" << std::endl;
		std::cout << " 5. [Admin] Manage Staff & Items" << std::endl;
		std::cout << " 6. [Create] New Customer" << std::endl;
		std::cout << " 0. [Exit]" << std::endl;
		std::cout << "Selection: ";

		if (!(std::cin >> choice))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			continue;
		}

		Clear();

		if (choice == 1)
		{
			std::cout << std::left << std::setw(10) << "ID" << std::setw(30) << "Restaurant Name" << std::endl;
			std::cout << std::setw(40) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
			for (int i = 0; i < m_RestaurantCount; i++)
			{
				std::cout << std::left << std::setw(10) << i << m_Restaurants[i]->GetRestaurantName() << std::endl;
			}

			int detailId;
			std::cout << "\nEnter Restaurant ID for full details (or -1 to return): ";
			std::cin >> detailId;

			if (detailId >= 0 && detailId < m_RestaurantCount)
			{
				Clear();
				std::cout << "--- " << m_Restaurants[detailId]->GetRestaurantName() << " Details ---\n";
				m_Restaurants[detailId]->GetManager()->DisplayInfo();
			}
		}
		else if (choice == 2)
		{
			std::cout << std::left << std::setw(10) << "ID" << std::setw(30) << "Restaurant Name" << std::endl;
			std::cout << std::setw(40) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
			for (int i = 0; i < m_RestaurantCount; i++)
			{
				std::cout << std::left << std::setw(10) << i << m_Restaurants[i]->GetRestaurantName() << std::endl;
			}

			int resId;
			std::cout << "\nEnter Restaurant ID: ";
			std::cin >> resId;

			if (resId >= 0 && resId < m_RestaurantCount)
			{
				std::cout << "\n--- Menu for " << m_Restaurants[resId]->GetRestaurantName() << " ---" << std::endl;
				m_Restaurants[resId]->DisplayMenu();
			}
		}
		else if (choice == 3)
		{
			std::cout << std::left << std::setw(10) << "ID" << std::setw(30) << "Customer Name" << std::endl;
			std::cout << std::setw(40) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
			for (int i = 0; i < m_CustomerCount; i++)
			{
				std::cout << std::left << std::setw(10) << i << m_Customers[i]->GetUserName() << std::endl;
			}

			int custId, resId;
			std::cout << "\nSelect Customer ID: ";
			std::cin >> custId;
			std::cout << "Select Restaurant ID: ";
			std::cin >> resId;

			if (custId >= 0 && custId < m_CustomerCount && resId >= 0 && resId < m_RestaurantCount)
			{
				Customer* customer = m_Customers[custId];
				Restaurant* res = m_Restaurants[resId];
				Order* order = customer->CreateOrder(res);

				int itemId = -1;
				while (true)
				{
					std::cout << "\n--- Adding items to order for " << customer->GetUserName() << " ---\n";
					res->DisplayMenu();
					std::cout << "Enter Item ID (0 to finish): ";
					std::cin >> itemId;
					if (itemId == 0) break;

					MenuItem* item = res->GetMenuItemById(itemId);
					if (item)
					{
						customer->AddItemToOrder(*item, order);
						std::cout << "Added: " << item->GetItemName() << std::endl;
					}
				}
				std::cout << "Order placed successfully!" << std::endl;
			}
		}
		else if (choice == 4)
		{
			int custId;
			std::cout << "Enter Customer ID: ";
			std::cin >> custId;
			if (custId >= 0 && custId < m_CustomerCount)
			{
				Order* order = m_Customers[custId]->GetLatestOrder();
				if (order) order->DisplayInfo();
				else std::cout << "No active orders." << std::endl;
			}
		}
		else if (choice == 5)
		{
			std::cout << "--- Management Panel ---\n";
			std::cout << "1. Hire Staff\n2. Add Menu Item\n3. View Full Restaurant Stats\nSelection: ";
			int adminChoice; std::cin >> adminChoice;

			int resId;
			std::cout << "Target Restaurant ID: "; std::cin >> resId;
			if (resId >= 0 && resId < m_RestaurantCount)
			{
				if (adminChoice == 1)
				{
					std::string name, email; int type;
					std::cout << "Type (1: Manager, 2: Courier): "; std::cin >> type;
					std::cout << "Name: "; std::cin.ignore(); std::getline(std::cin, name);
					std::cout << "Email: "; std::getline(std::cin, email);
					if (type == 1) m_Restaurants[resId]->SetManager(CreateManager(name, email, m_Restaurants[resId]));
					else m_Restaurants[resId]->AddEmployee(CreateDeliveryPerson(name, email, m_Restaurants[resId]));
				}
				else if (adminChoice == 2)
				{
					std::string name; double price; int type;
					std::cout << "Type (1: Food, 2: Drink): "; std::cin >> type;
					std::cout << "Name: "; std::cin.ignore(); std::getline(std::cin, name);
					std::cout << "Price: "; std::cin >> price;
					if (type == 1) m_Restaurants[resId]->AddMenuItem(*CreateFoodItem(name, price));
					else m_Restaurants[resId]->AddMenuItem(*CreateDrinkItem(name, price));
				}
				else if (adminChoice == 3)
				{
					Clear();
					std::cout << "--- MANAGER VIEW: " << m_Restaurants[resId]->GetRestaurantName() << " ---\n";
					m_Restaurants[resId]->GetManager()->DisplayInfo();
					std::cout << "\nCOURIER STAFF:\n";
					m_Restaurants[resId]->DisplayMenu();
				}
			}
		}
		else if (choice == 6)
		{
			std::string name, email, addr;
			std::cout << "New Customer Name: "; std::cin.ignore(); std::getline(std::cin, name);
			std::cout << "Email: "; std::getline(std::cin, email);
			std::cout << "Address: "; std::getline(std::cin, addr);
			CreateCustomer(name, email, addr);
			std::cout << "Customer created successfully!\n";
		}
	}
	std::cout << "Exiting system..." << std::endl;
}

void System::Clear() const
{
    for (int i = 0; i < 50; ++i) 
        std::cout << "\n";
}
