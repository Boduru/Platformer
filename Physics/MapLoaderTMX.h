#ifndef MAPLOADERTMX_H
#define MAPLOADERTMX_H

class MapLoaderTMX
{
	class Tileset
	{
	private:
		//Variables
		sf::Image tilesheet;

		int startTileNumber;
		int endTileNumber;
		int tileCount;
		int width;
		int height;
		int tilewidth;
		int tileheight;
		int columns;
		int rows;

		//Functions
		void createFromXML(pugi::xml_node& tileset_xml)
		{
			pugi::xml_document tileset_file_xml = MapLoaderTMX::getXMLFileContent(tileset_xml.attribute("source").as_string());

			this->startTileNumber = tileset_xml.attribute("firstgid").as_int();
			this->tilewidth = tileset_file_xml.select_node("tileset").node().attribute("tilewidth").as_int();
			this->tileheight = tileset_file_xml.select_node("tileset").node().attribute("tileheight").as_int();
			this->columns = tileset_file_xml.select_node("tileset").node().attribute("columns").as_int();
			this->tileCount = tileset_file_xml.select_node("tileset").node().attribute("tilecount").as_int();
			this->endTileNumber = this->startTileNumber + this->tileCount;
			this->rows = this->tileCount / this->columns;

			this->width = tileset_file_xml.select_node("tileset").node().child("image").attribute("width").as_int();
			this->height = tileset_file_xml.select_node("tileset").node().child("image").attribute("width").as_int();

			this->tilesheet.loadFromFile(tileset_file_xml.select_node("tileset").node().child("image").attribute("source").as_string());
		}

	public:
		//Constructors/Destructors
		Tileset(pugi::xml_node& tileset_xml)
		{
			this->createFromXML(tileset_xml);
		}

		//Accessors
		const int getStartTileNumber() const
		{
			return this->startTileNumber;
		}

		const int getEndTileNumber() const
		{
			return this->endTileNumber;
		}

		const int getTileCount() const
		{
			return this->tileCount;
		}

		const int getWidth() const
		{
			return this->width;
		}

		const int getHeight() const
		{
			return this->height;
		}

		const int getTileWidth() const
		{
			return this->tilewidth;
		}

		const int getTileHeight() const
		{
			return this->tileheight;
		}

		const int getColumns() const
		{
			return this->columns;
		}

		const int getRows() const
		{
			return this->rows;
		}

		const sf::Image& getTilesheet() const
		{
			return this->tilesheet;
		}
	};

private:
	//Functions
	static pugi::xml_document getXMLFileContent(std::string filename);
	static std::vector<MapLoaderTMX::Tileset> loadTilesets(pugi::xpath_node_set& content);
	static MapLoaderTMX::Tileset getTileset(std::vector<MapLoaderTMX::Tileset>& tilesets, int texture_number);
	static std::vector<Entity*> loadLayers(pugi::xpath_node_set& layers, std::vector<MapLoaderTMX::Tileset>& tilesets, int size);
	static sf::Vector2f getPlayerPosition();

public:
	//Static functions
	static std::vector<Entity*> loadMap(std::string map_file, int size);
};

#endif // !MAPLOADERTMX_H

