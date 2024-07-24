#include "Enemy.h"


// Name: Enemy(string name, int challenge)
// Description: Creates a new Enemy planet
// Preconditions: None
// Postconditions: Creates a new Enemy planet
Enemy::Enemy(string name, int challenge):Planet(name, challenge)
{

}


// Name: GetType
// Description: Returns type of planet
// Preconditions: None
// Postconditions: Returns the type of planet
string Enemy::GetType()
{
    return "enemy";
}
