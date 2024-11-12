#include "pathfinding.cpp"

int longessOfPath = 5;
enum Action
{
    idling,
    moving,
    fight
};

class GameObject
{
public:
    int ID;
    void                      assembleObject(int player, sf::Texture* texture, int width, int height, bool unitTakesSingleGrid_, bool movable, int x, int y);
    void                          createPath();
    sf::Sprite                  returnSprite();
    Action                      returnAction();
    int                    returnOwnerOfUnit();
    int                         returnUnitID();
    void                         setSelected();
    void                       setUnselected();
    void           commandToMove(int x, int y);
    void                          moveEntity();
    void                  updatePosVariables();
    int                                 unitID;
    bool                   unitTakesSingleGrid;
    int                         x_HashLongness;
    int                         y_HashLongness;
    bool                         unitIsMovable;
private:
    bool                          pathAlgorithmsIsDone = false;
    std::vector<Node>                                     path;
    std::vector<int>                            x_hashVEC = {};
    std::vector<int>                            y_hashVEC = {};
    int x_Pos, y_Pos, x_hash, y_hash, x_DestPoint, y_DestPoint;
    int                                            ownerOfUnit;
    int                                       pathIterable = 0;
    bool                                unitIsSelected = false;
    enum                              Action action { idling };
    sf::Sprite                                          sprite;
    int                                          x_currentHash;
    int                                          y_currentHash;
    int                                             x_DestHash;
    int                                             y_DestHash;
};

class Marine : public GameObject
{
public:
    const static int  WIDTH_SPRITE = 10;
    const static int HEIGHT_SPRITE = 10;
    virtual void spawn(int player, int x_Pos, int y_Pos) {
        assembleObject(player, &marine_texture, WIDTH_SPRITE, HEIGHT_SPRITE, true, true, x_Pos, y_Pos);
    }
private:
};


class Home : public GameObject
{
public:
    const static int  WIDTH_SPRITE = 60;
    const static int HEIGHT_SPRITE = 60;
    virtual void spawn(int player, int x_Pos, int y_Pos) {
        assembleObject(player, &marine_texture, WIDTH_SPRITE, HEIGHT_SPRITE, false, false, x_Pos, y_Pos);
    }
private:
};