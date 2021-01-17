#ifndef MAPLOADERJSON_H
#define MAPLOADERJSON_H

#include "nlohmann/json.hpp"

class MapLoaderJSON
{
private:
	//Functions
	static nlohmann::json getJSONFileContent(std::string filename);
	static sf::Image getTileSheet(std::string filename);
	static sf::Vector2u getTileSheetCellSize(sf::Image tilesheet, int tilesize);
	static std::vector<Entity*> loadLayers(sf::Image& tileSheet, nlohmann::json& layer, int startTileSize, sf::Vector2u tileSheetSize, float factor);

public:
	//Static functions
	static std::vector<Entity*> loadMap(std::string map_file, std::string tilesheet_file, int size);
};

#endif // !MAPLOADERJSON_H