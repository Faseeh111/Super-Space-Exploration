#include "Armor.h"

// Name: Armor(string name, string type, int value)
// Description: Creates a new Armor item
// Preconditions: None
// Postconditions: Can create a Armor item
Armor::Armor(string name, string type, int value):Item(name, type, value)
{

}
// Name: Display
// Description: Displays ARMOR, name, and value of armor
// Preconditions: None
// Postconditions: Displays information about the armor
void Armor::Display()
{
    // Used functions from Item class to indirectly access private varibales
    cout << ARMOR << GetName(); 
    cout << "(" << GetValue() << ")" << endl; 
}