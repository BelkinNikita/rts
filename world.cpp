#include "world.h"

void WorldObject::assembleObject(sf::Texture* texture, int width, int height, bool unitTakesSingleGrid_, int x, int y)
{
    x_Pos = x;
    y_Pos = y;
    x_hash = x_Pos / sizeOfHash;
    y_hash = y_Pos / sizeOfHash;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprites.push_back(&sprite);
    if (!unitTakesSingleGrid_)
    {
        x_HashLongness = (width / sizeOfHash) + 1;
        y_HashLongness = (height / sizeOfHash) + 1;
        for (int i = -1; i < x_HashLongness; ++i)  x_hashVEC.push_back(0);
        for (int i = -1; i < y_HashLongness; ++i) y_hashVEC.push_back(0);
    }
    if (unitTakesSingleGrid_)
    {
        mapHash[x_hash][y_hash] = 0;
    }
    else
    {
        for (int y = 0; y < y_HashLongness; ++y)
        {
            std::cout << "\n\n";
            for (int x = 0; x < x_HashLongness; ++x)
            {
                mapHash[y + y_hash][x + x_hash] = 0;
            }
        }  
        sprite.setPosition(x_Pos, y_Pos);
    }
}



