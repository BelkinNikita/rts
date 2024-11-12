#include "playerInput.h"



static void record(std::string information);
class Player 
{
	public:
		void							     handleInput();
		void                              clickLeftMouse();
		void                             clickRightMouse();
		void								  changeView();
		void 								 collideRect();
		void						   drawSelectingRect();
		sf::RectangleShape					  returnRect();
		bool							returnRECT_DRAWS();
		std::vector <GameObject*> returnAllunitsOfPlayer();
		void   addUnitToAllUnitsOfPlayer(GameObject* unit);
	private:
		bool				  LEFT_MOUSE_CLICKED   = false;
		bool			      RIGHT_MOUSE_CLICKED  = false;
		bool					        A_PRESSED  = false;
		bool  					    SHIFT_PRESSED  = false;
		bool  							RECT_DRAWS = false;
		sf::RectangleShape						 rectangle;
		sf::Vector2f							   RectPos;
		sf::Vector2f					          mousePos;
		std::vector <GameObject*>	         selectedUnits;
	    std::vector <GameObject*>		  allUnitsOfPlayer;
};


void Player::handleInput() 
{
	mousePos = WINDOW.mapPixelToCoords(sf::Mouse::getPosition(WINDOW));
	// std::cout << LEFT_MOUSE_CLICKED;
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::A)))					      		    { A_PRESSED = true; }
	else																		       { A_PRESSED = false; }

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::LShift)))							{ SHIFT_PRESSED = true; }
	else																		   { SHIFT_PRESSED = false; }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  {   if (LEFT_MOUSE_CLICKED == false)clickLeftMouse(); }
	else				 							      { LEFT_MOUSE_CLICKED = false; RECT_DRAWS = false; }
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) { if (RIGHT_MOUSE_CLICKED == false)clickRightMouse(); }	
	else																	 { RIGHT_MOUSE_CLICKED = false; }
																							 collideRect();
																						      changeView();
}

bool Player::returnRECT_DRAWS() { if (RECT_DRAWS) return RECT_DRAWS; }

void Player::collideRect() 
{
	if (LEFT_MOUSE_CLICKED == true) 
	{ 
		drawSelectingRect();
		for (GameObject* unit : players[thisPlayer]->returnAllunitsOfPlayer())
		{
			if (unit->returnSprite().getGlobalBounds().intersects(rectangle.getGlobalBounds()))
			{
				unit->setSelected();
				selectedUnits.push_back(unit);
			}
		}

	}	
}


void Player::changeView()
{
	if (mousePos.x > view.getCenter().x + 200 && view.getCenter().x < mapWidth - 300)  view.move(1, 0);
	else if (mousePos.x < view.getCenter().x - 200 && view.getCenter().x > 300)				  view.move(-1, 0);

	if (mousePos.y > view.getCenter().y + 200 && view.getCenter().y < mapWidth - 300)  view.move(0 , 1);
	else if (mousePos.y < view.getCenter().y - 200 && view.getCenter().y > 300)				  view.move(0, -1);
}


void Player::drawSelectingRect()
{
	if (RECT_DRAWS == false) 
	{
		RectPos = WINDOW.mapPixelToCoords(sf::Mouse::getPosition(WINDOW));
	}
	rectangle.setSize(sf::Vector2f(mousePos.x - RectPos.x, mousePos.y - RectPos.y)); 
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Green);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(RectPos.x, RectPos.y);
	RECT_DRAWS = true; 
};


void Player::clickLeftMouse()
{	
	if (!SHIFT_PRESSED)
	{
		for (GameObject* unit : units)
		{
			unit->setUnselected();
			selectedUnits.clear();
		}
	}
	for (GameObject* unit : units) 
	{
		sf::Sprite sprite = unit->returnSprite();
		sf::FloatRect bounds = sprite.getGlobalBounds();
		if (bounds.contains(mousePos))
		{
			unit->setSelected();
			selectedUnits.push_back(unit);
			//std::cout << "unit is selected \n";
			break;
		}
	}
	LEFT_MOUSE_CLICKED = true;
}


void Player::clickRightMouse()
{
	for (GameObject* unit : selectedUnits)
	{
		unit->commandToMove( mousePos.x, mousePos.y);
		record("m" + std::to_string(unit->returnOwnerOfUnit()) + std::to_string(unit->returnUnitID()) + " " +
			std::to_string(static_cast<int>(mousePos.x)) + " " + std::to_string(static_cast<int>(mousePos.y)) + " ");
		/*for (int x = 0; x < size(mapSector); ++x)
		{
			std::cout <<"\n";
			
			for (int j = 0; j < size(mapSector[0]); ++j) 
			{
				std::cout << mapSector[x][j];
			}
		}
		//std::cout << "mouse: " << std::to_string(mousePos.x) << "\n"; */		
	}
	RIGHT_MOUSE_CLICKED = true;
}

std::vector <GameObject*>		 Player::returnAllunitsOfPlayer() { return allUnitsOfPlayer; }

void Player::addUnitToAllUnitsOfPlayer(GameObject* unit) { allUnitsOfPlayer.push_back(unit); }

sf::RectangleShape									Player::returnRect() { if (RECT_DRAWS) return rectangle; }




static void input(Player* player)
{	
	player->handleInput();
}


