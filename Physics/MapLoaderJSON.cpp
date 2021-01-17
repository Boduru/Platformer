#include "stdafx.h"

//Functions
nlohmann::json MapLoaderJSON::getJSONFileContent(std::string filename)
{
    //Read the JSON file
    std::ifstream raw_file(filename);
    nlohmann::json content;
    raw_file >> content;

    raw_file.close();

    return content;
}

sf::Image MapLoaderJSON::getTileSheet(std::string filename)
{
    sf::Image tilesheet;
    tilesheet.loadFromFile(filename);

    return tilesheet;
}

sf::Vector2u MapLoaderJSON::getTileSheetCellSize(sf::Image tilesheet, int tilesize)
{
    sf::Vector2u tilesheet_size = tilesheet.getSize();
    tilesheet_size.x /= tilesize;
    tilesheet_size.y /= tilesize;

    return tilesheet_size;
}

std::vector<Entity*> MapLoaderJSON::loadLayers(sf::Image& tileSheet, nlohmann::json& layers, int startTileSize, sf::Vector2u tileSheetSize, float factor)
{
    std::vector<Entity*> entities;
    sf::Texture current_texture;

    for (short layer_idx = 0; layer_idx < layers.size(); layer_idx++)
    {
        nlohmann::json& layer = layers[layer_idx]["chunks"];

        //Each chunk contains a list of datas
        for (short chunk_idx = 0; chunk_idx < layer.size(); chunk_idx++)
        {
            for (short row = 0; row < startTileSize; row++)
            {
                for (short column = 0; column < startTileSize; column++)
                {
                    //Check weather or not the chunk contains some datas
                    if (layer[chunk_idx].size() > 0)
                    {
                        //Get the texture number
                        int texture_number = layer[chunk_idx]["data"][row * startTileSize + column] - 1;

                        //If the texture was not 0 which means no block in this cell
                        if (texture_number > -1)
                        {
                            //Retrieve row and column of the texture_number from the tilesheet (z = (x, y))
                            int texture_row = floor(texture_number / tileSheetSize.x);
                            int texture_column = -1 * tileSheetSize.x * texture_row + texture_number;

                            //Setup texture image
                            current_texture.loadFromImage(tileSheet, sf::IntRect(texture_column * startTileSize, texture_row * startTileSize, startTileSize, startTileSize));

                            //Get the current chunk parameters
                            int x = layer[chunk_idx]["x"];
                            int y = layer[chunk_idx]["y"];
                            int w = layer[chunk_idx]["width"];
                            int h = layer[chunk_idx]["height"];

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

//Static functions
//Main loading function
std::vector<Entity*> MapLoaderJSON::loadMap(std::string map_file, std::string tilesheet_file, int size)
{
    //Load JSON file content
    nlohmann::json content = MapLoaderJSON::getJSONFileContent(map_file);

    //Retrieve useful values from the JSON file
    int startTileSize = content["tilewidth"];

    //New ratio (resize all the images)
    float factor = size / startTileSize;

    //Load up the tilesheet as an Image to extract easily singles images
    sf::Image tilesheet = MapLoaderJSON::getTileSheet(tilesheet_file);

    //Get the number of cells in the tilesheet
    sf::Vector2u tilesheetSize = MapLoaderJSON::getTileSheetCellSize(tilesheet, startTileSize);

    //Process the map creation
    return MapLoaderJSON::loadLayers(tilesheet, content["layers"], startTileSize, tilesheetSize, factor);
}