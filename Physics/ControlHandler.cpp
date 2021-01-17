#include "stdafx.h"

//Constructors/Destructors
ControlHandler::ControlHandler()
{
	this->initContols();
}

//Functions
void ControlHandler::initContols()
{
	//Keyboard controls
	this->controls["UP"] = sf::Keyboard::Key::Up;
	this->controls["RIGHT"] = sf::Keyboard::Key::Right;
	this->controls["LEFT"] = sf::Keyboard::Key::Left;
	this->controls["END"] = sf::Keyboard::Key::Escape;
	this->controls["BACKSPACE"] = sf::Keyboard::Key::BackSpace;
	this->controls["TAB"] = sf::Keyboard::Key::Tab;
	this->controls["RESIZE"] = sf::Keyboard::Key::F;
	this->controls["PAUSE"] = sf::Keyboard::Key::P;

	//All useful keys
	this->controls["a"] = sf::Keyboard::Key::A;
	this->controls["b"] = sf::Keyboard::Key::B;
	this->controls["c"] = sf::Keyboard::Key::C;
	this->controls["d"] = sf::Keyboard::Key::D;
	this->controls["e"] = sf::Keyboard::Key::E;
	this->controls["f"] = sf::Keyboard::Key::F;
	this->controls["g"] = sf::Keyboard::Key::G;
	this->controls["h"] = sf::Keyboard::Key::H;
	this->controls["i"] = sf::Keyboard::Key::I;
	this->controls["j"] = sf::Keyboard::Key::J;
	this->controls["k"] = sf::Keyboard::Key::K;
	this->controls["l"] = sf::Keyboard::Key::L;
	this->controls["m"] = sf::Keyboard::Key::M;
	this->controls["n"] = sf::Keyboard::Key::N;
	this->controls["o"] = sf::Keyboard::Key::O;
	this->controls["p"] = sf::Keyboard::Key::P;
	this->controls["q"] = sf::Keyboard::Key::Q;
	this->controls["r"] = sf::Keyboard::Key::R;
	this->controls["s"] = sf::Keyboard::Key::S;
	this->controls["t"] = sf::Keyboard::Key::T;
	this->controls["u"] = sf::Keyboard::Key::U;
	this->controls["v"] = sf::Keyboard::Key::V;
	this->controls["w"] = sf::Keyboard::Key::W;
	this->controls["x"] = sf::Keyboard::Key::X;
	this->controls["y"] = sf::Keyboard::Key::Y;
	this->controls["z"] = sf::Keyboard::Key::Z;
	this->controls["0"] = sf::Keyboard::Key::Numpad0;
	this->controls["1"] = sf::Keyboard::Key::Numpad1;
	this->controls["2"] = sf::Keyboard::Key::Numpad2;
	this->controls["3"] = sf::Keyboard::Key::Numpad3;
	this->controls["4"] = sf::Keyboard::Key::Numpad4;
	this->controls["5"] = sf::Keyboard::Key::Numpad5;
	this->controls["6"] = sf::Keyboard::Key::Numpad6;
	this->controls["7"] = sf::Keyboard::Key::Numpad7;
	this->controls["8"] = sf::Keyboard::Key::Numpad8;
	this->controls["9"] = sf::Keyboard::Key::Numpad9;
	this->controls[" "] = sf::Keyboard::Key::Space;

	//Mouse controls
	this->buttons["LEFT"] = sf::Mouse::Left;
	this->buttons["RIGHT"] = sf::Mouse::Right;
}

std::map<std::string, sf::Keyboard::Key> ControlHandler::getInputs(sf::Event& event)
{
	/*Return the keys that are tapped just once*/

	std::map<std::string, sf::Keyboard::Key> tapped;

	for (auto& c : this->controls)
	{
		if (event.key.code == c.second)
			tapped.emplace(c);
	}

	return tapped;
}

std::map<std::string, sf::Keyboard::Key> ControlHandler::getInputsPressed()
{
	/*Return all the supported keys that are currently pressed*/

	std::map<std::string, sf::Keyboard::Key> pressed;

	for (auto& c : this->controls)
	{
		if (sf::Keyboard::isKeyPressed(c.second))
			pressed.emplace(c);
	}

	return pressed;
}

std::map<std::string, sf::Mouse::Button> ControlHandler::getButtons(sf::Event& event)
{
	/*Return the buttons that are tapped just once*/

	std::map<std::string, sf::Mouse::Button> tapped;

	for (auto& c : this->buttons)
	{
		if (event.key.code == c.second)
			tapped.emplace(c);
	}

	return tapped;
}

std::map<std::string, sf::Mouse::Button> ControlHandler::getButtonsPressed()
{
	/*Return all the supported buttons that are currently pressed*/

	std::map<std::string, sf::Mouse::Button> pressed;

	for (auto& c : this->buttons)
	{
		if (sf::Mouse::isButtonPressed(c.second))
			pressed.emplace(c);
	}

	return pressed;
}