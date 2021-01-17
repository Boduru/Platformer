#include "stdafx.h"

pugi::xml_document MapLoaderTMX::getXMLFileContent(std::string filename)
{
	pugi::xml_document content;

	if (!content.load_file(filename.c_str()))
		return pugi::xml_document();

	return content;
}

std::vector<Entity*> MapLoaderTMX::loadLayers(pugi::xpath_node_set& layers, std::vector<MapLoaderTMX::Tileset>& tilesets, int size)
{
	std::vector<Entity*> entities;
	sf::Texture current_texture;

	int startTileSize = 16;
	int factor = 1;
	
	for (short layer_idx = 0; layer_idx < layers.size(); layer_idx++)
	{
		pugi::xpath_node_set chunks = layers[layer_idx].node().child("data").select_nodes("chunk");

		//Each chunk contains a list of datas
		for (short chunk_idx = 0; chunk_idx < chunks.size(); chunk_idx++)
		{
			for (auto raw_cells : chunks[chunk_idx].node())
			{
				std::stringstream raw_datas;
				raw_cells.print(raw_datas, "", pugi::format_raw);
				std::vector<std::string> cells = Utils::split(raw_datas.str(), ',');

				for (short row = 0; row < startTileSize; row++)
				{
					for (short column = 0; column < startTileSize; column++)
					{
						//Get the texture number
						int texture_number = std::stoi(cells[row * startTileSize + column]);

						//If the texture was not 0 which means no block in this cell
						if (texture_number > 0)
						{
							MapLoaderTMX::Tileset tileset = MapLoaderTMX::getTileset(tilesets, texture_number);
							sf::Image tilesheet = tileset.getTilesheet();

							//Retrieve row and column of the texture_number from the tilesheet (z = (x, y))
							int texture_row = floor(texture_number - tileset.getStartTileNumber()) / tileset.getColumns();
							int texture_column = floor(texture_number - tileset.getStartTileNumber()) - texture_row * tileset.getColumns();
							float factor = size / tileset.getTileWidth();

							//Setup texture image
							current_texture.loadFromImage(tilesheet, sf::IntRect(texture_column * startTileSize, texture_row * startTileSize, startTileSize, startTileSize));

							//Get the current chunk parameters
							int x = chunks[chunk_idx].node().attribute("x").as_int();
							int y = chunks[chunk_idx].node().attribute("y").as_int();
							int w = chunks[chunk_idx].node().attribute("width").as_int();
							int h = chunks[chunk_idx].node().attribute("height").as_int();

							//Append the Entity to the list
							Entity* entity = new Entity(current_texture, sf::Vector2f((column + x) * w, (row + y) * h), sf::Vector2u(1, 1));
							entity->resize(factor);
							entities.push_back(entity);
						}
					}
				}
			}
		}
	}

	return entities;
}

std::vector<MapLoaderTMX::Tileset> MapLoaderTMX::loadTilesets(pugi::xpath_node_set& content)
{
	std::vector<MapLoaderTMX::Tileset> tilesets;

	for (int i = 0; i < content.size(); i++)
	{
		pugi::xml_node current_tileset_xml = content[i].node();
		Tileset tileset(current_tileset_xml);
		tilesets.push_back(tileset);
	}

	return tilesets;
}

MapLoaderTMX::Tileset MapLoaderTMX::getTileset(std::vector<MapLoaderTMX::Tileset>& tilesets, int texture_number)
{
	for (MapLoaderTMX::Tileset tileset : tilesets)
	{
		if (texture_number >= tileset.getStartTileNumber() && texture_number < tileset.getEndTileNumber())
			return tileset;
	}
}

//Static Functions
std::vector<Entity*> MapLoaderTMX::loadMap(std::string map_file, int size)
{
	//Map preferences
	pugi::xml_document content = MapLoaderTMX::getXMLFileContent(map_file);

	//Map nodes
	pugi::xml_node map_xml = content.child("map");
	pugi::xpath_node_set tilesets_xml = map_xml.select_nodes("tileset");
	pugi::xpath_node_set layers_xml = map_xml.select_nodes("layer");
	pugi::xpath_node_set objectGroups_xml = map_xml.select_nodes("objectgroup");

	//Load tilesets
	std::vector<MapLoaderTMX::Tileset> tilesets = MapLoaderTMX::loadTilesets(tilesets_xml);

	//Load layers
	std::vector<Entity*> entities = MapLoaderTMX::loadLayers(layers_xml, tilesets, size);
	
	return entities;
}
