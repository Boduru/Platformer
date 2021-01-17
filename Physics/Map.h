#ifndef MAP_H
#define MAP_H

class Entity;

class Map
{
private:
	//Arrays containing the map elements
	std::map<std::array<int, 2>, std::vector<Entity*>> entities;

	//Size of a cell within the virtual grid
	int cellSize;

public:
	//Constructors/Destructors
	Map(std::string map_file, std::string tilesheet_file, int size);
	Map(std::string map_file, int size);
	virtual ~Map();

	//Accessors
	sf::Vector2i getGridPosition(const sf::Vector2f position) const;
	std::vector<Entity*> getInEntities(Entity& element);
	std::vector<Entity*> getEntitiesFromMap(std::vector<std::array<int, 2>> keys);
	std::vector<std::array<int, 2>> getCellsFromElement(Entity& element);
	std::vector<Entity*> getEntitiesFromCell(std::array<int, 2> cell);
	std::map<std::array<int, 2>, std::vector<Entity*>>& getMap();

	const int getCellSize() const;

	//Functions
	void loadMapFromJSON(std::string filename, std::string tilesheet_file, int size);
	void loadMapFromTMX(std::string filename, int size);
	void addEntity(Entity* entity);
};

#endif // !MAP_H