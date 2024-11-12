#include "resources.cpp"
#include "gameObjects.h"


void GameObject::assembleObject(int player, sf::Texture* texture, int width, int height, bool unitTakesSingleGrid_, bool movable, int x, int y)
{
    unitIsMovable                                 = movable;
    ownerOfUnit                                    = player;
    x_Pos                                               = x;
    y_Pos                                               = y;
    unitTakesSingleGrid              = unitTakesSingleGrid_;
    x_hash = x_Pos / sizeOfHash;
    y_hash = y_Pos / sizeOfHash;
    if (!unitTakesSingleGrid)
    { 
        x_HashLongness = (width  / sizeOfHash) + 1;
        y_HashLongness = (height / sizeOfHash) + 1;
        for (int i = -1; i < x_HashLongness + 1; ++i)  x_hashVEC.push_back(ownerOfUnit);
        for (int i = -1; i < y_HashLongness + 1; ++i) y_hashVEC.push_back(ownerOfUnit);
    }
    sprite.setTexture                            (*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprites.push_back                             (&sprite);
    units.push_back                                  (this);
    addUnitToPlayerArray                (this, ownerOfUnit);
    unitID      = returnUnitNumberOfPlayer(ownerOfUnit) - 1;   
    updatePosVariables();
}


Action GameObject::    returnAction()          { return action; }

sf::Sprite GameObject::returnSprite()          { return sprite; }

int GameObject::  returnOwnerOfUnit()     { return ownerOfUnit; }

int GameObject::       returnUnitID()          { return unitID; }

void GameObject::       setSelected()  { unitIsSelected = true; }

void GameObject::     setUnselected() { unitIsSelected = false; }


void GameObject::     commandToMove(int x, int y)
    { 
    pathAlgorithmsIsDone = false;
		pathIterable = 0;
        x_DestPoint = x; 
        y_DestPoint = y;
        action = { moving };
		path.clear();
        createPath();
       // std::cout << "unit moves \n" << x << " and " << y;
    }


void GameObject::moveEntity()
{
        //std::cout << "x_current: " << x_Pos / sizeOfHash << " y_current: " << y_Pos / sizeOfHash << "\n";
        //std::cout << "x_path: " << path[0][1] << " y_path:: " << path[0][0] << "\n";
        if (x_Pos > x_DestPoint && mapHash[y_hash][x_hash - 1] == -1)  x_Pos = x_Pos - 1;
       else if (x_Pos < x_DestPoint && mapHash[y_hash][x_hash + 1] == -1)  x_Pos = x_Pos + 1;
        if (y_Pos > y_DestPoint && mapHash[y_hash - 1][x_hash] == -1)  y_Pos = y_Pos - 1;
        else if (y_Pos < y_DestPoint && mapHash[y_hash + 1][x_hash] == -1)  y_Pos = y_Pos + 1;
        //if (x_Pos > x_DestPoint)  x_Pos = x_Pos - 1;
        //else if (x_Pos < x_DestPoint)  x_Pos = x_Pos + 1;
        //if (y_Pos > y_DestPoint)  y_Pos = y_Pos - 1;
        //else if (y_Pos < y_DestPoint)  y_Pos = y_Pos + 1;
        updatePosVariables();

if (x_hash == x_DestPoint / sizeOfHash && y_hash == y_DestPoint / sizeOfHash)
{
    if (path.size() > pathIterable + 1 )
{
    ++pathIterable;
    std::cout << "new";
    x_DestPoint = path[pathIterable].x * sizeOfHash;
    y_DestPoint = path[pathIterable].y * sizeOfHash;
}
else
{
    action = { idling };
}

    }
}


 void GameObject::createPath()
   {
       path = aStar(x_Pos / sizeOfHash, y_Pos / sizeOfHash, x_DestPoint / sizeOfHash, y_DestPoint / sizeOfHash);
       if (!path.empty()) {
           std::cout << "Path found:\n";
           for (const Node& node : path) {
               std::cout << "(" << node.x << ", " << node.y << ") ";
           }
           std::cout << std::endl;
           x_DestPoint = path[0].x * sizeOfHash;
           y_DestPoint = path[0].y * sizeOfHash;
           std::cout << "y_DestHash" << y_DestHash << " x_DestHash: : " << x_DestHash <<"\n";
       }
       else {
           std::cout << "No path found.\n";
           action = { idling };
       }
   }


                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                /*
					findPath();

					for (int i = 0; i < size(path) - 1; ++i)
					{
						std::cout <<"path is found: " << path[i][1] << " " << path[i][0] << "\n ";
					}
                    x_DestPoint = path[0][1] * sizeOfHash;
                    y_DestPoint = path[0][0] * sizeOfHash;
			
            } 
			if (x_hash == path[pathIterable][1] && y_hash == path[pathIterable][0])
			{
                if (longessOfPath > pathIterable)
				{
					pathIterable = 0;
					path.clear();
					action = idling;
					pathAlgorithmsIsDone = false;
				}
				else
				{
                    ++pathIterable;
                    x_DestPoint = path[pathIterable][1] * sizeOfHash;
                    y_DestPoint = path[pathIterable][0] * sizeOfHash;
                    std::cout << "next step: " << pathIterable << "\n";
				}
			*/





void GameObject::updatePosVariables()
{
    if (unitTakesSingleGrid)
    {
    mapHash[y_hash][x_hash] = -1;
    x_hash = x_Pos / sizeOfHash;
    y_hash = y_Pos / sizeOfHash;
    mapHash[y_hash][x_hash] = ownerOfUnit;
    sprite.setPosition(x_Pos, y_Pos);
    //record();

    }
    else
    {
        for (int y = 0; y < y_HashLongness; ++y)
        {
      
            for (int x = 0; x < x_HashLongness; ++x)
            {
                mapHash[y + y_hash][x + x_hash] = -1;
            }
        }

        x_hash = x_Pos / sizeOfHash;
        y_hash = y_Pos / sizeOfHash;
        
        
        for (int y = 0; y < y_HashLongness; ++y)
        {
            for (int x = 0; x < x_HashLongness; ++x)
            {
                mapHash[y + y_hash][x + x_hash] = ownerOfUnit;
            }
        }
        sprite.setPosition(x_Pos, y_Pos);
    }
    if (ownerOfUnit == thisPlayer) setSectorUnfogged(x_Pos, y_Pos);
}


/*
void GameObject::findPath()
{
    std::cout << "finding a path... ";
    x_currentHash = x_hash;
    y_currentHash = y_hash;
    x_DestHash = x_DestPoint / sizeOfHash;
    y_DestHash = y_DestPoint / sizeOfHash;
    while (!pathAlgorithmsIsDone)
    {
        std::cout << x_currentHash << "\n";
        if (path.size() < longessOfPath)
        {
            findPath_x();
        }
        else 
        {
            pathAlgorithmsIsDone = true;
        }
    }
}

void GameObject::findPath_x()
{
    if (x_DestHash > x_currentHash)
    {
        int x_step = ++x_currentHash;
        std::vector<int> step{ y_currentHash, x_step };
        path.push_back(step);
        findPath_y();
    }
    else if (x_currentHash > x_DestHash)
    {
        int x_step = --x_currentHash;
        std::vector<int> step{ y_currentHash, x_step };
        path.push_back(step);
        findPath_y();
    }
    else
    {
        int x_step = x_currentHash;
        std::vector<int> step{ y_currentHash, x_step };
        findPath_y();
    }
    

}



void GameObject::findPath_y()
{
    if (y_DestHash > y_currentHash)
    {
        int y_step = ++y_currentHash;
        std::vector<int> step{ y_step, x_currentHash };
        path.push_back(step);
        std::cout << x_DestHash;
    }
    else if (y_currentHash > y_DestHash)
    {
        int y_step = --y_currentHash;
        std::vector<int> step{ y_step, x_currentHash };
        path.push_back(step);
        std::cout << x_DestHash;
    }
    else
    {
        int y_step = y_currentHash;
        std::vector<int> step{ y_step, x_currentHash };
        path.push_back(step);
        std::cout << x_DestHash;
    }
}

*/
