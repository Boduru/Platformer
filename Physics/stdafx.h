//Base includes
#include <sstream>
#include <array>
#include <string>
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>

//SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//External dependencies (nugget)
#include <nlohmann/json.hpp>
#include "pugixml.hpp"

//Game includes
#include "Utils.h"

#include "Animation.h"
#include "Animator.h"

#include "Label.h"
#include "Button.h"
#include "TextInput.h"
#include "ComboBox.h"
#include "DropBox.h"
#include "Slider.h"

#include "Entity.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "MapLoaderTMX.h"
#include "MapLoaderJSON.h"
#include "Map.h"
#include "ControlHandler.h"
#include "Player.h"
#include "Level.h"
#include "BoxCollider.h"

#include "State.h"
#include "PauseInternState.h"
#include "MainMenuState.h"
#include "LevelChooserState.h"
#include "SettingsState.h"
#include "GameState.h"
#include "Game.h"