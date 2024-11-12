
class WorldObject
{ 
public:
    void assembleObject(sf::Texture* texture, int width, int height, bool unitTakesSingleGrid_, int x, int y);
    int ID;
    bool                   unitTakesSingleGrid;
    int                          x_HashLongness;
    int                          y_HashLongness;
    std::vector<int> x_hashVEC = {};
    std::vector<int> y_hashVEC = {};
    int x_Pos, y_Pos, x_hash, y_hash, x_DestPoint, y_DestPoint;
    bool                                unitIsSelected = false;
    sf::Sprite                                          sprite;
};


class Hill : public WorldObject
{
public:
    const static int  WIDTH_SPRITE = 80;
    const static int HEIGHT_SPRITE = 40;
    virtual void spawn(int x_Pos, int y_Pos) {
        assembleObject(&fifth_texture, WIDTH_SPRITE, HEIGHT_SPRITE, false, x_Pos, y_Pos);
    }
};