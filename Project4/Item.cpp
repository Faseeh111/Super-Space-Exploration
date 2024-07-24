#include "Item.h"

// Name: Item(string name, string type, int value) - Overload constructor
// Description: Creates a new item of a specific type
// Preconditions: None
// Postconditions: Used by all child classes
Item::Item(string name, string type, int value)
{
    m_name = name;
    m_type = type;
    m_value = value;
}


// Name: ~Item - Virtual Destructor
// Description: Required because child classes exist
// Preconditions: None
// Postconditions: Nothing to deallocate
Item::~Item()
{
    cout << "Destructing base" << endl;
}


// Name: GetType()
// Description: Returns the type of item
// Preconditions: None
// Postconditions: Returns type of item (weapon, armor, or engine)
string Item::GetType()
{
    return m_type;
}


// Name: GetName()
// Description: Returns the name of item
// Preconditions: None
// Postconditions: Returns name of item
string Item::GetName()
{
    return m_name;
}


// Name: GetValue
// Description: Gets Value of item
// Preconditions: None
// Postconditions: Returns value of item
int Item::GetValue()
{
    return m_value;
}


// // Name: Display()
// // Description: Used in child classes for special attacks
// // Preconditions: None
// // Postconditions: Used to call child class SpecialAttack
// void Item::Display()
// {
//     cout << "Items Displaying" << endl;
// }