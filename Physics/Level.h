#ifndef LEVEL_H
#define LEVEL_H

class Entity;
class Map;

class Level
{
private:
	//Variables
	std::string name;
	Map* currentMap;

	//Arrays containing the level elements(maps)
	std::map<std::string, Map> maps;

public:
	//Constructors/Destructors
	Level(std::string filePath, std::string name);
	virtual ~Level();

	//Setup Functions
	void createLevel(const std::string file);

	//Functions
	void updateLevel(Entity& camera, Player& player, const float deltaTime);
	void updatePlayerCollisions(Player& player, const float deltaTime);
	void updateEntities(Entity& camera, const float deltaTime);
	void updateEntitiesCollisions(Entity& camera, const float deltaTime);

	void drawLevel(sf::RenderWindow& window, Entity& camera);
};

#endif // !LEVEL_H