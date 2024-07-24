#include "Game.h"


// Name: Game(string itemFile, string planetFile) - Overloaded Constructor
// Description: Creates a new Game by setting m_fileItems and m_filePlanets
// Preconditions: None
// Postconditions: Sets two file names in Game
Game::Game(string fileItems, string filePlanets)
{
    m_fileItems = fileItems;
    m_filePlanets = filePlanets;
}


// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated
//                 in Game (ship, items, and planets)
Game::~Game()
{
    // Empties out m_item
    for (unsigned int i = 0; i < m_items.size(); i++)
    {
        delete m_items[i];
    }
    m_items.clear();

    // Empties out m_planets
    for (unsigned int i = 0; i < m_planets.size(); i++)
    {
        delete m_planets[i];
    }
    m_planets.clear();

    // Deletes ship 
    if (m_ship)
    {
        delete m_ship;
        m_ship = nullptr;
    }
}


// Name: LoadItems()
// Description: Dynamically allocates items and inserts them into
//              the m_items vector
// Note: the number of items is NOT known - you should not use constants
// Hint: Use getline(file,variable,delimiter) - may also use stoi
// Precondition: m_itemFile is populated
// Postcondition: m_items is populated
void Game::LoadItems()
{

    ifstream inputFile(m_fileItems);
    if (!inputFile.is_open())
    {
        cout << "Error: Unable to open file " << m_fileItems << endl;
        return;
    }

    string name, type;
    int value;
    int count = 0; // Will be used to determine total items loaded

    while (getline(inputFile, name, ','))
    {
        // Getting info with getline, stops at a comma
        getline(inputFile, type, ',');

        // Using insertion operator for int value
        inputFile >> value;
        inputFile.ignore(1); // Ignore the new line

        Item* newItem = nullptr;

        if (type == "armor") 
        {
            newItem = new Armor(name, type, value);
        }
        if (type == "weapon") 
        {
            newItem = new Weapon(name, type, value);
        }
        if (type == "engine")
        {
            newItem = new Engine(name, type, value);
        }

        m_items.push_back(newItem); 

        count++;

    }

    cout << count << " items loaded" << endl;

}


// Name: LoadPlanets()
// Description: Dynamically allocates items and inserts them into
//              the m_planets vector
// Note: the number of planets is NOT known - you should NOT use constants
// Hint: Use getline(file,variable,delimiter) - may also use stoi
// Precondition: m_planetFile is populated
// Postcondition: m_planets is populated
void Game::LoadPlanets()
{
    ifstream inputFile(m_filePlanets);
    if (!inputFile.is_open())
    {
        cout << "Error: Unable to open file " << m_filePlanets << endl;
        return;
    }

    string name, type; 
    int value;
    int count = 0; // Will be used to determine total planets loaded

    while (getline(inputFile, name, ','))
    {
        // Getting info with getline, stops at a comma
        getline(inputFile, type, ',');

        // Using insertion operator for int value
        inputFile >> value;
        inputFile.ignore(1); // Ignore the new line

        Planet* newPlanet = nullptr;

        if (type == "mining") 
        {
            newPlanet = new Mining(name, value);
        }
        if (type == "gas") 
        {
            newPlanet = new Gas(name, value);
        }
        if (type == "enemy")
        {
            newPlanet = new Enemy(name, value);
        }

        m_planets.push_back(newPlanet); 

        count++;

    }

    cout << count << " planets loaded" << endl;
}


// Name: ShipCreation()
// Description: Populates m_ship and asks name (sets name of ship)
//              Also adds items (START_ENGINE, START_ARMOR, START_WEAPON)
// Preconditions: None
// Postconditions: m_ship is populated
void Game::ShipCreation()
{
    string shipName;
    cout << "Enter your ships name: " << endl;
    // Used getline to allow user to put in multiple words
    getline(cin, shipName);
    m_ship = new Ship(shipName);

    // Adding all starter items
    m_ship->AddItem(m_items[START_ARMOR]);
    m_ship->AddItem(m_items[START_ENGINE]);
    m_ship->AddItem(m_items[START_WEAPON]);
}


// Name: StartGame()
// Description: Welcomes the player to the game. "Super Space Exploration"
//              Calls LoadPlanets, LoadItems, ShipCreation, sets the m_curPlanet (0)
//              randomizes m_winEngine based on UTOPIA_MAX and UTOPIA_MIN
//              Finally, calls Action (which is the main menu)
// Preconditions: Input files must exist
// Postconditions: All game components loaded to play game
void Game::StartGame()
{
    cout << "Welcome to Super Space Exploration!" << endl;
    LoadPlanets();
    LoadItems();
    ShipCreation();
    // Sets to start planet
    m_curPlanet = m_planets[START_PLANET];

    int winCondition = UTOPIA_MIN + rand() % (UTOPIA_MAX - UTOPIA_MIN + 1); // Holds win condition 30-50
    m_winEngine = winCondition;

    Action();

}


// Name: Action()
// Description: Menu for game. Displays menu.
//              Player can examine the ship's items, move, attack planet,
//              Try to travel to Utopia, check stats, or quit
//              Player dies in one of two ways: 1. <= 0 fuel or
//                   2. Tries to go to Utopia but doesn't have high enough engine
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until quit or player dies
void Game::Action()
{
    int choice; // This holds choice selection of player on what to do
    // Do while loop for user input validation
    do
    {
        cout << "What would you like to do?" << endl;
        cout << "1. Examine Items" << endl;
        cout << "2. Move" << endl;
        cout << "3. Attack Planet" << endl;
        cout << "4. Travel to Utopia" << endl;
        cout << "5. Check Stats" << endl;
        cout << "6. Quit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            DisplayShipItems();
            break;
        case 2:
            Move();
            break;
        case 3:
            AttackPlanet();
            break;
        case 4:
            TravelUtopia();
            break;
        case 5:
            Stats();
            break;
        case 6:
            cout << "Goodbye!" << endl;
            break;
        default:
            // This would run if the user does not input a number from 1-6
            cout << "Invalid choice. Please try again." << endl;
        }
    } while ((choice != 6) && (m_ship->GetFuel() > 0));
}
// Name: Move
// Description: Moves ship to new random location
//              Charges MOVE_FUEL as cost to move to new planet
//              Displays information about new planet
// Preconditions: Must be valid move (may go to same planet more than once)
// Postconditions: Displays planet information and reduces fuel
void Game::Move()
{
    // Displays message for if fuel reaches zero
    if (m_ship->GetFuel() <= 0)
    {
        cout << "You have ran out of fuel, you lose!" << endl;
    }

    cout << "You travel to the next planet" << endl;
    int random_move = rand() % m_planets.size() + 1; // Randomly selects index for which planet is picked
    m_curPlanet = m_planets[random_move - 1]; 

    // Prints out the planet using overloaded operator <<
    cout << *m_curPlanet << endl;

    //Changes fuel by move fuel amount which is -5 fuel
    m_ship->ModifyFuel(MOVE_FUEL);
}


// Name: AttackPlanet
// Description: Allows ship to attack a planet
//              1. Checks if planet already defeated (displays message if already won)
//              2. Calls Planet's battle with ship (if not already defeated)
//              3. Displays if win or not. Can attack again if not defeated.
//              4. If winner, Identifies an item load on ship
// Preconditions: None
// Postconditions: Fuel may be below zero. May get new item.
void Game::AttackPlanet()
{
    if (m_curPlanet->GetIsExplored() == true)
    {
        cout << "Already defeated" << endl;
    }
    else 
    {
        // This checks if you won the battle
        if (m_curPlanet->Battle(m_ship) == true)
        {
            // Finds an item matching difficulty to reward you with
            IdentifyItem(m_curPlanet->GetChallenge());
        }
    }
}


// Name: IdentifyItem(int challenge)
// Description: Randomly identifies an item of the challenge's level
//              Calls AddItem in ship and tries to add the item
// Preconditions: None
// Postconditions: Will try to add an item to the ship of a random type
void Game::IdentifyItem(int challenge)
{
    m_curPlanet->GetChallenge();
    int pickItem = rand() % m_items.size(); // Randomly selects a potential item reward
    // m_ship->AddItem(m_items[pickItem - 1]);
    bool stop = false; // This will stop the while loop when an item is added

    while(stop == false)
    {
        // Checks if the values are the same level as change
        if (m_items[pickItem - 1]->GetValue() == challenge)
        {
            m_ship->AddItem(m_items[pickItem - 1]);
            stop = true;
        }

        // Rerandomize if not matched up
        pickItem = rand() % m_items.size();
    }
    
}


// Name: Stats()
// Description: Calls the ship's display function
// Preconditions: None
// Postconditions: None
void Game::Stats()
{
    m_ship->DisplayShip();
}


// Name: TravelUtopia()
// Description: Attempts to win game if total engine value > m_engineValue
//              if total engine value is below UTOPIA_MIN, returns 0
//              If total engine value above m_engineValue, returns 1
//              If total engine value below m_engineValue, returns -1
// Preconditions: None
// Postconditions: -1 = lose; 0 = continue, 1 = win
int Game::TravelUtopia()
{
    // Warning for if your engines are below 30 level
    if ( m_ship->GetTotal("engine") < UTOPIA_MIN)
    {
        cout << "Warning, you cant travel to utopia yet! Upgrade your engine" << endl;
        return 0;
    }
    else if (m_ship->GetTotal("engine") > m_winEngine)
    {
        cout << "You win!" << endl;
        return 1;
    }
    else 
    {
        cout << "You lose, engine requirements not met." << endl;
        return -1;
    }
}


// Name: DisplayShipItems
// Description: Displays a numbered list of all items on ship
// Preconditions: m_items has items in it otherwise says No Items Found
// Postconditions: None
void Game::DisplayShipItems()
{
    m_ship->DisplayItems();
}