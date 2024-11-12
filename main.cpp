#include "main.h"


#include "test.cpp"
#include "time.cpp"





std::mutex m;
std::thread t1(runNetwork);
Minimap* minimap = new Minimap;
int main()
{
	initializate();
	//WINDOW.setFramerateLimit(5);
	//WINDOW.setVerticalSyncEnabled(true);

	while (WINDOW.isOpen())
	{
		while (WINDOW.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				WINDOW.close();
			}
		}
		players[thisPlayer] -> handleInput();
		update();
		render();
		timeUpdate();
	}
	return 0;
}
static void test() {
	for (int i = 0; i < 2; ++i)
	{
		Player* player = new Player;
		players.push_back(player);
	}
	for (int i = 1; i < 5; ++i)
	{
		Marine* marine = new Marine;
		marine->spawn(0, 50 * i, 50 * i);
	}
	for (int i = 1; i < 10; ++i)
	{
		Home* marine = new Home;
		marine->spawn(1, 90 * i, 50 * i);
	}
	for (int i = 1; i < 10; ++i)
	{
		Hill* hill = new Hill;
		hill->spawn(80 * i, 70 * i);
	}
}

void initializate()
{
	loadTextures();
	createHashList();

	//mainPath();
	test();
}


void loadTextures() 
{
	marine_texture.loadFromFile("data/marine.png");
	fifth_texture.loadFromFile("data/5.png");
}
 

void render()
{
	WINDOW.setView(view);
	WINDOW.clear(DARKGRAY);
	for (sf::Sprite* sprite : sprites) {
		WINDOW.draw(*sprite); 
	}
	createfogOfWar();
	if (players[thisPlayer]->returnRECT_DRAWS()) WINDOW.draw(players[thisPlayer]-> returnRect());
	WINDOW.display();
}

static void createfogOfWar() {
	for (int i = 0; i < size(mapSector); ++i)
	{
		for (int j = 0; j < size(mapSector[0]); ++j)
		{
			if (mapSector[i][j]->returnSectorIsFogged()) { WINDOW.draw(mapSector[i][j]->returnFog()); }
		}
	}
}

void countFPS()
{ 
}

static void record(std::string information)
{
	std::string out = information;
	network->send(out);
	//if (youAreHost) client->send(out);
	//else			server->send(out);
	//const char transcription[] = { "x"};
	//std::cout << "got: " << x << "\n";
}


void addUnitToPlayerArray(GameObject* unit, int player)				{ (players[player]->addUnitToAllUnitsOfPlayer(unit)); }

int returnUnitNumberOfPlayer(int player)				   { return (players[player] -> returnAllunitsOfPlayer().size()); }

static std::vector <GameObject*> returnAllunitsOfPlayer(int player) { return (players[player]->returnAllunitsOfPlayer()); }



void setSectorUnfogged(int x, int y) { mapSector[y / 200][x / 200]->sectorIsUnfogged(); }