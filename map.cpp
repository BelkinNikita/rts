
class Cell
{
public:
void createForOfWar()
    {

    }
};

class Sector
{
public:
    std::vector <GameObject*> UnitsInSector_;
    std::vector <GameObject*> playerUnits_;
    sf::RectangleShape fog;
    Cell a;
    Cell b;
    Cell c;
    Cell d;
    void createFogOfWar(int z, int y)
    {      
            
            fog.setSize(sf::Vector2f(sizeOfSector, sizeOfSector));
            fog.setFillColor(sf::Color::Black);
            fog.setPosition(z * sizeOfSector, y * sizeOfSector);
        
    }
    bool SectorIsFogged = true;
    void setFogOfWar(Sector* sector)
    {
        SectorIsFogged = false;
    }

    void sectorIsUnfogged()
    {
        SectorIsFogged = false;
    }
    bool returnSectorIsFogged()
    {
        return SectorIsFogged;
    }
    sf::RectangleShape returnFog() { return fog; }
};




static void createSectorList()
{
    
    std::vector<Sector*> row;
    int z = 0;
    int y = 0;
    for (int i = 0; i < (mapWidth / sizeOfSector) ; ++i)
    {
        z = 0;
        for (int j = 0; j < (mapHeight / sizeOfSector) ; ++j)
        {
            Sector* sector = new Sector;
            sector->createFogOfWar(z, y);
            row.push_back(sector);
            ++z;
        }
        mapSector.push_back(row);
        row.clear();
        ++y;
    }
}


static void setEdgesOfMapPathless()
{
    for (int i = 0; i < size(mapHash); ++i)
    {
        mapHash[i][0] = 0;
        mapHash[i][size(mapHash[0])-1] = 0;
    }
    for (int i = 0; i < size(mapHash[0]) - 1; ++i)
    { 
        mapHash[0][i] = 0;
        mapHash[size(mapHash) - 1][i] = 0;
    }
}


static void createHashList() 
{
    std::vector<int> row;
    for (int i = 0; i < mapWidth / sizeOfHash; ++i)
    {
        for (int j = 0; j < mapHeight / sizeOfHash; ++j)
        {
            int x = -1;
            row.push_back(x);
        }
        mapHash.push_back(row);
        row.clear();
    }
    setEdgesOfMapPathless();
    createSectorList();
}





class Minimap
{
public:
    void draw()
    {
        for (int i = 0; i < size(mapHash); ++i)
        {
            for (int j = 0; j < size(mapHash); ++j)
            {
                sf::RectangleShape grid;
                switch (mapHash[i][j])
                {
                case -1:
                    grid.setSize(sf::Vector2f(1, 1));
                    grid.setFillColor(sf::Color::Black);
                    grid.setPosition(j, i + 500);
                    WINDOW.draw(grid);
                    break;
                case 0:
                    grid.setSize(sf::Vector2f(1, 1));
                    grid.setFillColor(sf::Color::Green);
                    grid.setPosition(j, i + 500);
                    WINDOW.draw(grid);
                    break;
                }
            }
        }
    }
};





