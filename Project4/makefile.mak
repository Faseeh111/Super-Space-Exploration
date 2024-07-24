CXX = g++

CXXFLAGS = -Wall -g

proj4: Item.o Weapon.o Ship.o Engine.o Armor.o Planet.o Gas.o Mining.o Enemy.o Game.o proj4.cpp
	$(CXX) $(CXXFLAGS) Item.o Weapon.o Ship.o Engine.o Armor.o Planet.o Gas.o Mining.o Enemy.o Game.o proj4.cpp -o proj4

Game.o: Item.o Weapon.o Ship.o Engine.o Armor.o Planet.o Gas.o Mining.o Enemy.o Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Enemy.o: Planet.o Enemy.h Enemy.cpp
	$(CXX) $(CXXFLAGS) -c Enemy.cpp

Mining.o: Planet.o Mining.h Mining.cpp
	$(CXX) $(CXXFLAGS) -c Mining.cpp

Gas.o: Planet.o Gas.h Gas.cpp
	$(CXX) $(CXXFLAGS) -c Gas.cpp

Planet.o: Ship.o Planet.h Planet.cpp
	$(CXX) $(CXXFLAGS) -c Planet.cpp

Armor.o: Item.o Armor.h Engine.cpp
	$(CXX) $(CXXFLAGS) -c Armor.cpp

Engine.o: Item.o Engine.h Engine.cpp
	$(CXX) $(CXXFLAGS) -c Engine.cpp

Ship.o: Item.o Ship.h Ship.cpp
	$(CXX) $(CXXFLAGS) -c Ship.cpp

Weapon.o: Item.o Weapon.h Weapon.cpp
	$(CXX) $(CXXFLAGS) -c Weapon.cpp

Item.o: Item.h Item.cpp
	$(CXX) $(CXXFLAGS) -c Item.cpp

clean:
	rm .o
	rm *~

run:
	./proj4 proj4_items.txt proj4_planets.txt

val1:
	valgrind ./proj4 proj4_items.txt proj4_planets.txt