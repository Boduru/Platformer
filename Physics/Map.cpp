#include "stdafx.h"

//Constructors/Destructors
Map::Map(std::string map_file, std::string tilesheet_file, int size)
    : cellSize(256)
{
    if (map_file != "" && tilesheet_file != "")
        this->loadMapFromJSON(map_file, tilesheet_file, size);
}

Map::Map(std::string map_file, int size)
    : cellSize(256)
{
    if (map_file != "")
        this->loadMapFromTMX(map_file, size);
}

Map::~Map()
{
    for (auto it = this->entities.begin(); it != this->entities.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            it->second[i] = nullptr;
        }
    }
}

//Accessors
sf::Vector2i Map::getGridPosition(const sf::Vector2f position) const
{
    /*Return the 2d grid position (i, j) from the actual world position*/

    int x = static_cast<int>(floor(position.x / this->cellSize));
    int y = static_cast<int>(floor(position.y / this->cellSize));

    return sf::Vector2i(x, y);
}

std::vector<Entity*> Map::getEntitiesFromMap(std::vector<std::array<int, 2>> keys)
{
    std::vector<Entity*> vec;

    //For all the cells
    for (int i = 0; i < keys.size(); i++)
    {
        std::array<int, 2> cell = keys[i];

        //If the map contains the cell number
        if (this->entities.find(cell) != this->entities.end())
        {
            //Loop through the vector inside the cell
            for (int j = 0; j < this->entities.at(cell).size(); j++)
            {
                //Check if the entity is not already in the vector
                if (std::find(vec.begin(), vec.end(), this->entities.at(cell)[j]) == vec.end())
                    vec.push_back(this->entities.at(cell)[j]);
            }
        }
    }

    return vec;
}

std::vector<std::array<int, 2>> Map::getCellsFromElement(Entity& element)
{
    /*Return the cells the entity is on*/

    std::vector<std::array<int, 2>> vec;

    sf::Vector2i topleft = this->getGridPosition(element.getTopLeft());
    sf::Vector2i bottomright = this->getGridPosition(element.getBottomRight());

    for (int i = topleft.y; i <= bottomright.y; i++)
    {
        for (int j = topleft.x; j <= bottomright.x; j++)
        {
            std::array<int, 2> p = { j, i };
            vec.push_back(p);
        }
    }

    return vec;
}

std::vector<Entity*> Map::getEntitiesFromCell(std::array<int, 2> cell)
{
    if (this->entities.count(cell) > 0)
        return this->entities.at(cell);
    else
        return std::vector<Entity*>();
}

std::map<std::array<int, 2>, std::vector<Entity*>>& Map::getMap()
{
    return this->entities;
}

std::vector<Entity*> Map::getInEntities(Entity& element)
{
    return this->getEntitiesFromMap(this->getCellsFromElement(element));
}

const int Map::getCellSize() const
{
    return this->cellSize;
}

//Functions
void Map::loadMapFromJSON(std::string map_file, std::string tilesheet_file, int size)
{
    std::vector<Entity*> entities = MapLoaderJSON::loadMap(map_file, tilesheet_file, size);

    for (int i = 0; i < entities.size(); i++)
    {
        this->addEntity(entities[i]);
    }
}

void Map::loadMapFromTMX(std::string filename, int size)
{
    std::vector<Entity*> entities = MapLoaderTMX::loadMap(filename, 64);

    for (int i = 0; i < entities.size(); i++)
    {
        this->addEntity(entities[i]);
    }
}

void Map::addEntity(Entity* entity)
{
    /*Add the entity on the grid using its four box vertices
    and place them in the map*/

    std::vector<std::array<int, 2>> cells = this->getCellsFromElement(*entity);

    for (int i = 0; i < cells.size(); i++)
        this->entities[cells[i]].push_back(entity);
}