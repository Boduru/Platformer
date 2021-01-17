#include "stdafx.h"

//Constructors/Destructors
State::State() : State(States::Main, 0.f, 0.f)
{
}

State::State(const States& state, const float& width, const float& height)
	: state(state)
{
	this->camera = Camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(width, height));
	this->configure();
}

State::~State()
{
}

//Accessors
const States State::getState() const
{
	return this->state;
}

Camera& State::getCamera()
{
	return this->camera;
}

const std::vector<Label> State::getLabels() const
{
	return this->labels;
}

const std::vector<Button> State::getButtons() const
{
	return this->buttons;
}

const std::vector<TextInput> State::getInputs() const
{
	return this->inputs;
}

const std::vector<ComboBox> State::getComboboxes() const
{
	return this->comboboxes;
}

const std::vector<Slider> State::getSliders() const
{
	return this->sliders;
}

const std::vector<DropBox> State::getDropboxes() const
{
	return this->dropboxes;
}

void State::configure()
{
	this->configureLabels();
	this->configureButtons();
	this->configureInputs();
	this->configureComboboxes();
	this->configureSliders();
	this->configureDropboxes();
}

void State::configureLabels()
{
}

void State::configureButtons()
{
}

void State::configureInputs()
{
}

void State::configureComboboxes()
{
}

void State::configureSliders()
{
}

void State::configureDropboxes()
{
}

//Functions
void State::update(std::map<std::string, sf::Keyboard::Key> pressed,
	std::map<std::string, sf::Keyboard::Key> released, 
	std::map<std::string, sf::Keyboard::Key> tapped, 
	std::map<std::string, sf::Mouse::Button> clicked, 
	std::map<std::string, sf::Mouse::Button> uncliked, 
	std::map<std::string, sf::Mouse::Button> one_hit_click,
	sf::Vector2i mouse_pos_view,
	sf::Vector2f mouse_pos_window,
	const float deltatime)
{
	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i].update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	for (int i = 0; i < this->comboboxes.size(); i++)
		this->comboboxes[i].update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	for (int i = 0; i < this->inputs.size(); i++)
		this->inputs[i].update(deltatime, tapped, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	for (int i = 0; i < this->sliders.size(); i++)
		this->sliders[i].update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	for (int i = 0; i < this->dropboxes.size(); i++)
		this->dropboxes[i].update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);
}

void State::updateView(sf::RenderWindow& window, const float& deltatime)
{
	this->camera.update(window, sf::Vector2f(0, 0));
}

void State::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->labels.size(); i++)
		this->labels[i].draw(&window);

	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i].draw(&window);

	for (int i = 0; i < this->inputs.size(); i++)
		this->inputs[i].draw(&window);

	for (int i = 0; i < this->comboboxes.size(); i++)
		this->comboboxes[i].draw(&window);

	for (int i = 0; i < this->sliders.size(); i++)
		this->sliders[i].draw(&window);

	for (int i = 0; i < this->dropboxes.size(); i++)
		this->dropboxes[i].draw(&window);
}