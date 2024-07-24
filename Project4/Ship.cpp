#include "Ship.h"

// Name: Ship(string) - Overloaded ship
// Description: Creates a new ship that can hold items (MAX_ITEMS)
//              and Fuel (STARTING_FUEL). Populates m_name
// Preconditions: None
// Postconditions: A new ship
Ship::Ship(string name)
{
	m_name = name;
	m_fuel = STARTING_FUEL;
} 	


// Name: GetName()
// Description: Returns m_name
// Preconditions: None
// Postconditions: Returns ship's m_name
string Ship::GetName()
{
	return m_name;
}


// Name: GetTotal(string type)
// Description: Passed an item type (armor, weapon, or engine)
//     Iterates over all items on ship and totals type passed in
// Preconditions: None
// Postconditions: Returns total value for armor, weapon, or engine
int Ship::GetTotal(string type)
{
	int total = 0;

	for(unsigned int i = 0; i < m_shipItems.size(); i++)
	{
		// Checks if type is the same
		if (m_shipItems[i]->GetType() == type)
		{
			total += m_shipItems[i]->GetValue();
		}
	}

	return total;
}


// Name: AddItem
// Description: Adds a new item into m_items up to MAX_ITEMS.
//    If at max, calls ReplaceItem
// Preconditions: None
// Postconditions: m_items is populated
void Ship::AddItem(Item * item)
{
	int itemTotal = GetItemCount(); // Holds total amount of ship items
	// cout << "TOTAL" << itemTotal << endl;

	if (itemTotal < MAX_ITEMS)
	{
		m_shipItems.push_back(item);
	}
	else
	{
		ReplaceItem(item);
	}

}


// Name: ReplaceItem(Item*)
// Description: Used when m_shipItem is at capacity.
//   Lists all ship items and replaces with updated pointer
//   Does NOT make a new object - just updates pointer
// Preconditions: None
// Postconditions: Used to replace an item in inventory (m_shipItems)
void Ship::ReplaceItem(Item * item)
{
    // Shows user all the items
    DisplayItems();
    int replacedItem; // holds value that replaces item

    // Loop until the user enters a valid item number
    do
    {
        cout << "Enter the number of the item you want to replace: ";
        cin >> replacedItem;

        // Input validation
        if (replacedItem < 1 || replacedItem > static_cast<int>(m_shipItems.size()))
        {
            cout << "Invalid item number. Please enter a number between 1 and " << m_shipItems.size() << "." << endl;
        }
    } while (replacedItem < 1 || replacedItem > static_cast<int>(m_shipItems.size()));

    // Replace the item outside the loop after input validation
    m_shipItems[replacedItem - 1] = item;
}




// Name: GetFuel
// Description: Returns fuel
// Preconditions: None
// Postconditions: Returns m_fuel
int Ship::GetFuel()
{
	return m_fuel;
}


// Name: ModifyFuel(int)
// Description: Used to increase (positive int) or
//              decrease (negative int) m_fuel
// Preconditions: None
// Postconditions: Used to update fuel.
void Ship::ModifyFuel(int fuel)
{
	cout << "Your fuel has been modified by " << fuel << " fuel" << endl;
	m_fuel += fuel;
}


// Name: DisplayItems
// Description: Displays a numbered list of all items on ship.
// Preconditions: None
// Postconditions: m_items is populated
void Ship::DisplayItems()
{
	for(int i = 0; i < GetItemCount(); i++)
	{
		cout << i + 1 << ". ";
		m_shipItems[i]->Display();
	}
}


// Name: GetItemCount();
// Description: Returns number of items in m_shipItems
// Preconditions: None
// Postconditions: Returns items in m_shipItems
int Ship::GetItemCount()
{
	int count = 0; // This will hold amount of items existing

	for(unsigned int i = 0; i < m_shipItems.size(); i++)
	{
		count++;
	}

	return count;
}
// Name: DisplayShip;
// Description: Displays stats about the ship
// Displays name, fuel, attack(weapon), defense(armor), engine(engine) all all items
// Preconditions: None
// Postconditions: None
void Ship::DisplayShip()
{
	cout << "**************************" << endl;
	cout << "Name: " << GetName() << endl;
	cout << "Fuel: " << GetFuel() << endl;
	cout << "Attack: " << GetTotal("weapon") << endl;
	cout << "Defense: " << GetTotal("armor") << endl;
	cout << "Engine: " << GetTotal("engine") << endl;
	cout << "**************************" << endl;
	DisplayItems();
}
