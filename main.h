#include <iostream>
#include <vector>
#include <list>
#include <csignal>
#include <atomic>

#include <cstdlib>
#include <future>
#include <mutex>



#include "SFML/Graphics.hpp"
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>



//var
const int  mainWindowWidth = 800;
const int mainWindowHeigth = 800;
sf::RenderWindow WINDOW(sf::VideoMode(mainWindowWidth, mainWindowHeigth), "stratezhka");
const sf::Color DARKGRAY = { 55, 55, 55, 255 };
sf::Event event;
bool youAreHost;
int thisPlayer = 0;

//ref
class WorldObject;
class Hill;
class GameObject;
class Player;
class Sector;


void													   render();
static void										   createfogOfWar();
void												 loadTextures();
void							    				 initializate();
int						       returnUnitNumberOfPlayer(int player);
static std::vector <GameObject*> returnAllunitsOfPlayer(int player);



//game objects
std::vector	  <GameObject*> units;
std::vector     <Player*> players;
std::vector <sf::Sprite*> sprites;
void addUnitToPlayerArray(GameObject* unit, int player);


//map 
std::vector<std::vector<int> >		 mapHash;
std::vector<std::vector<Sector*> > mapSector;
std::vector <sf::RectangleShape>    fogOfWar;
const int sizeOfHash = 20;
const int sizeOfSector = 200;
const int sizeOfCell = 50;
void setSectorUnfogged(int x, int y);
const int mapWidth = 2000;
const int mapHeight = 2000;

sf::View view(sf::FloatRect(0.f, 0.f, 900, 900));
sf::View minimapView(sf::FloatRect(0.f, 0.f, mapWidth, mapHeight));

#include "gameObjects.cpp"
#include "update.cpp"
#include "playerInput.cpp"

#include "render.cpp"

#include "map.cpp"
#include "network.cpp"
#include "tracker.cpp"
#include "world.cpp"




