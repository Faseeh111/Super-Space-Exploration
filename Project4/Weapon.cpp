#include "Weapon.h"


// Name: Weapon(string name, string type, int value)
// Description: Creates a new Weapon item
// Preconditions: None
// Postconditions: Can create a Weapon
Weapon::Weapon(string name, string type, int value):Item(name, type, value)
{

}


// Name: Display
// Description: Displays WEAPON, name, and value of weapon
// Preconditions: None
// Postconditions: Displays information about the weapon
void Weapon::Display()
{
    cout << WEAPON << GetName();
    cout << "(" << GetValue() << ")" << endl;
}