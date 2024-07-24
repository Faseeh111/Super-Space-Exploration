#include "Mining.h"


// Name: Mining(string name, int challenge)
// Description: Creates a new Mining planet
// Preconditions: None
// Postconditions: Creates a new Mining planet
Mining::Mining(string name, int challenge):Planet(name, challenge)
{

}


// Name: GetType
// Description: Returns type of planet
// Preconditions: None
// Postconditions: Returns the type of planet
string Mining::GetType()
{
    return "mining";
}