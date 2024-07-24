#include "Gas.h"


// Name: Gas(string name)
// Description: Creates a new Gas planet with name and challenge
// Preconditions: None
// Postconditions: Creates a new Gas planet
Gas::Gas(string name, int challenge):Planet(name, challenge)
{

}


// Name: GetType
// Description: Returns type of planet
// Preconditions: None
// Postconditions: Returns the type of planet
string Gas::GetType()
{
    return "gas";
}