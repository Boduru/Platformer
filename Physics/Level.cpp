#include "stdafx.h"

//Constructors/Destructors
Level::Level(std::string filePath, std::string name)
	: name(name)
{
	this->createLevel(filePath);
}

Level::~Level()
{

}

//Functions
void Level::createLevel(const std::string file)
{
	Map map("..//Resources/Maps/level_1.tmx", 64);
	
	this->maps.emplace("SunRoad", map);

	this->currentMap = &this->maps.at("SunRoad");
}

void Level::updateLevel(Entity& camera, Player& player, const float deltaTime)
{
	//this->updateEntitiesCollisions(camera, deltaTime);
	//this->updateEntities(camera, deltaTime);
	this->updatePlayerCollisions(player, deltaTime);
}

void Level::updatePlayerCollisions(Player& player, const float deltaTime)
{
	//Get all the near block to update them and the the collisions
	std::vector<Entity*> entities = this->currentMap->getInEntities(player);

	for (unsigned i = 0; i < entities.size(); i++) {
		if (BoxCollider::isOverlap(player, *entities[i]))
			BoxCollider::doResponse(player, *entities[i]);
	}
}

void Level::updateEntities(Entity& camera, const float deltaTime)
{
	//Get all the near block to update them
	std::vector<Entity*> entities = this->currentMap->getInEntities(camera);

	for (unsigned i = 0; i < entities.size(); i++)
		entities[i]->update(deltaTime);
}

void Level::updateEntitiesCollisions(Entity& camera, const float deltaTime)
{
	//Get all the near block to update them and the the collisions
	/*std::vector<Entity*> entities = this->getBlockFromMap(this->entities, this->getCellsFromElement(camera));

	for (unsigned i = 0; i < entities.size(); i++) {
		for (unsigned j = 0; j < entities.size(); j++) {
			if (entities[i] != entities[j]) {
				//BoxCollider::isOverlap(entities[i], entities[j]);
			}
		}
	}*/
}

void Level::drawLevel(sf::RenderWindow& window, Entity& camera)
{
	//Draw background image repeat if needed

	std::vector<Entity*> entities = this->currentMap->getInEntities(camera);
	std::sort(entities.begin(), entities.end(), Entity::DepthCompare);

	for (int i = 0; i < entities.size(); i++)
		entities[i]->draw(window);
}