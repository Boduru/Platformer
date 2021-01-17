#ifndef UTILS_H
#define UTILS_H

//GLOBAL LINKS
const std::string RESOURCES_PATH = "..//Resources//";
const std::string AUDIO_PATH = RESOURCES_PATH + "Audio//";
const std::string FONT_PATH = RESOURCES_PATH + "Fonts//";
const std::string IMAGE_PATH = RESOURCES_PATH + "Images//";
const std::string GUI_PATH = IMAGE_PATH + "GUI//";
const std::string BACKGROUND_PATH = IMAGE_PATH + "Backgrounds//";
const std::string MUSIC_PATH = RESOURCES_PATH + "Musics//";
const std::string TILESET_PREFERENCES_PATH = RESOURCES_PATH + "Tilesets//";
const std::string TILESETS_IMAGES_PATH = IMAGE_PATH + "Tilesets//";
const std::string MAP_PATH = RESOURCES_PATH + "Maps//";
const std::string PREFERENCES_PATH = RESOURCES_PATH + "Preferences//";

//SPECIAL LINKS
const std::string FONT_BASIC = FONT_PATH + "Fipps-Regular.otf";

const std::string PLAYER_PREFERENCES = PREFERENCES_PATH + "playerPrefs.pref";
const std::string GAME_PREFERENCES = PREFERENCES_PATH + "gamePrefs.pref";

class Utils
{
public:
	static int sign(double value);
	static std::vector<std::string> split(const std::string& s, char delim);
	static std::string getNthLineContent(const std::string& file_path, const int& line);
};

#endif // !UTILS_H