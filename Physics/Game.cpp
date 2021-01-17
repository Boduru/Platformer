#include "stdafx.h"

/*
    DISCLAIMER :
    Manage the whole game by creating the window and updating it,
    retrieving the keys inputted, the mouse position and button pressed,
    keeping up the frame rate,
    handling the states (Menu, Options, Game), updating and drawing the game.
*/

//Constructors/Destructors
Game::Game(unsigned short width, unsigned short height, std::string windowName)
    : name(windowName), frameRateLimit(120), paused(false),
    minSize(sf::Vector2f(width, height)), mediumSize(sf::Vector2f(1600, 1040)), maxSize(sf::Vector2f(1920, 1080))
{
    //Window drawing settings
    sf::ContextSettings cs = sf::ContextSettings();
    cs.antialiasingLevel = 16;

    //Object creation
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, cs);
    this->clock = sf::Clock();
    this->controller = ControlHandler();
    this->pauseState = new PauseInternState(States::Pause, width, height);
    //this->state = new GameState(States::Play, width, height);
    //this->state = new MainMenuState(States::Main, width, height);
    //this->state = new SettingsState(States::Settings, width, height);
    this->state = new LevelChooserState(States::LevelChooser, width, height);

    //Options
    this->desktop = sf::VideoMode::getDesktopMode();
    this->window->setKeyRepeatEnabled(false);
    this->window->setFramerateLimit(this->frameRateLimit);

    this->configureGame();
}

Game::~Game()
{
    delete this->pauseState;
    delete this->state;
    delete this->window;
}

//Accessors
float Game::getDeltaTime()
{
    /*Get the deltaTime in seconds*/

    float delta = this->clock.restart().asSeconds();

    //Adjust deltatime if too big (if window paused or another problem)
    if (delta > 0.1)
        delta = 0;

    return delta;
}

//Functions
void Game::toggleFullScreen()
{
    float width = this->maxSize.x;
    float height = this->maxSize.y;

    if (width == this->window->getSize().x)
    {
        width = this->minSize.x;
        height = this->minSize.y;
    }

    this->changeWindowSize(width, height);
}

void Game::changeWindowSize(float width, float height)
{
    this->resizeWindow(width, height);
    this->window->setSize(sf::Vector2u(width, height));
    this->window->setView(this->state->getCamera().getView());
    this->window->setPosition(sf::Vector2i(
        this->desktop.getDesktopMode().width / 2 - this->window->getSize().x / 2,
        this->desktop.getDesktopMode().height / 2 - this->window->getSize().y / 2)
    );
}

void Game::resizeWindow(const float width, const float height)
{
    /*Change the scale and size of the window*/

    this->state->getCamera().restretch(width, height);
}

void Game::endGame()
{
    /*Close down the window and end the game*/

    this->window->close();
}

void Game::configureGame()
{
    std::ifstream prefs;
    prefs.open(GAME_PREFERENCES);

    std::string line;

    //SET FPS
    getline(prefs, line);

    this->frameRateLimit = std::stoi(line.substr(line.find(':') + 1, -1));
    this->window->setFramerateLimit(this->frameRateLimit);

    //SET Window size
    getline(prefs, line);
    line = line.substr(line.find(':') + 1, -1);

    if (line == "small")
        this->changeWindowSize(this->minSize.x, this->minSize.y);

    else if (line == "medium")
        this->changeWindowSize(this->mediumSize.x, this->mediumSize.y);

    if (line == "large")
        this->changeWindowSize(this->maxSize.x, this->maxSize.y);

    prefs.close();
}

void Game::checkWindowEvents()
{
    if (this->released.find("END") != this->released.end() && this->state->getState() != States::Play)
        this->endGame();

    else if (this->released.find("RESIZE") != this->released.end() && this->state->getState() == States::Play)
        this->toggleFullScreen();

    else if (this->released.find("PAUSE") != this->released.end() && this->state->getState() == States::Play)
        this->paused ^= true;
}

void Game::updateEvents()
{
    sf::Event event;

    this->released = std::map<std::string, sf::Keyboard::Key>();
    this->tapped = std::map<std::string, sf::Keyboard::Key>();
    this->oneHitClicked = std::map<std::string, sf::Mouse::Button>();
    this->unclicked = std::map<std::string, sf::Mouse::Button>();

    while (this->window->pollEvent(event))
        this->updateWindowEvents(event);

    this->updateKeyboardEvents();
    this->updateMouseEvents();
    this->updateMousePosition();
    this->checkWindowEvents();
}

void Game::updateWindowEvents(sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        this->endGame();
        break;

    case sf::Event::Resized:
        this->resizeWindow(float(this->window->getSize().x), float(this->window->getSize().y));
        break;

    case sf::Event::KeyPressed:
        this->tapped = this->controller.getInputs(event);
        break;

    case sf::Event::KeyReleased:
        this->released = this->controller.getInputs(event);
        break;

    case sf::Event::MouseButtonPressed:
        this->oneHitClicked = this->controller.getButtons(event);
        break;

    case sf::Event::MouseButtonReleased:
        this->unclicked = this->controller.getButtons(event);
        break;

    default:
        break;
    }
}

void Game::updateKeyboardEvents()
{
    /*Update the keyboard events when pressing continuously keys*/

    this->pressed = this->controller.getInputsPressed();
}

void Game::updateMouseEvents()
{
    /*Update the mouse events when pressing continuously buttons*/

    this->clicked = this->controller.getButtonsPressed();
}

void Game::updateMousePosition()
{
    this->mousePosView = sf::Mouse::getPosition(*this->window);
    this->mousePosWindow = this->window->mapPixelToCoords(this->mousePosView);
}

void Game::manageStates()
{
    //Choose the right state to use in function of the events

    switch (this->state->getState())
    {
    case States::Main:
        this->manageMainMenuState();
        break;

    case States::Play:
        this->manageGameState();
        break;

    case States::Settings:
        this->manageSettingsState();
        break;

    case States::Network:
        this->manageNetworkingState();
        break;

    default:
        break;
    }
}

void Game::manageMainMenuState()
{
    for (int i = 0; i < this->state->getButtons().size(); i++)
    {
        if (this->state->getButtons()[i].isButtonClicked())
        {
            if (this->state->getButtons()[i].getButtonName() == "PLAY")
            {
                this->state = new GameState(States::Play, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->state->getButtons()[i].getButtonName() == "SETTINGS")
            {
                this->state = new SettingsState(States::Settings, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->state->getButtons()[i].getButtonName() == "LEVEL_CHOOSER")
            {
                this->state = new LevelChooserState(States::LevelChooser, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->state->getButtons()[i].getButtonName() == "QUIT")
                this->endGame();
        }
    }
}

void Game::manageSettingsState()
{
    for (int i = 0; i < this->state->getButtons().size(); i++)
    {
        if (this->state->getButtons()[i].isButtonClicked())
        {
            if (this->state->getButtons()[i].getButtonName() == "VALIDATE")
            {
                this->configureGame();
                this->state = new MainMenuState(States::Main, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->state->getButtons()[i].getButtonName() == "DISCARD")
            {
                this->state = new MainMenuState(States::Main, this->window->getSize().x, this->window->getSize().y);
                break;
            }
        }
    }
}

void Game::manageLevelChooserState()
{
    for (int i = 0; i < this->state->getButtons().size(); i++)
    {
        if (this->state->getButtons()[i].isButtonClicked())
        {
            if (this->state->getButtons()[i].getButtonName() == "VALIDATE")
            {
                this->configureGame();
                this->state = new MainMenuState(States::Main, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->state->getButtons()[i].getButtonName() == "DISCARD")
            {
                this->state = new MainMenuState(States::Main, this->window->getSize().x, this->window->getSize().y);
                break;
            }
        }
    }
}

void Game::manageGameState()
{
}

void Game::manageNetworkingState()
{
}

void Game::managePauseState()
{
    for (int i = 0; i < this->pauseState->getButtons().size(); i++)
    {
        if (this->pauseState->getButtons()[i].isButtonClicked())
        {
            if (this->pauseState->getButtons()[i].getButtonName() == "RESUME")
            {
                this->paused = false;
                break;
            }

            else if (this->pauseState->getButtons()[i].getButtonName() == "RETURN")
            {
                this->paused = false;
                this->state = new MainMenuState(States::Main, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->pauseState->getButtons()[i].getButtonName() == "LEVEL_CHOOSER")
            {
                this->paused = false;
                this->state = new LevelChooserState(States::LevelChooser, this->window->getSize().x, this->window->getSize().y);
                break;
            }

            else if (this->pauseState->getButtons()[i].getButtonName() == "SETTINGS")
            {
                this->paused = false;
                this->state = new SettingsState(States::Settings, this->window->getSize().x, this->window->getSize().y);
                break;
            }
        }
    }
}

void Game::run()
{
    /*Main game loop*/

    while (this->window->isOpen())
    {
        //Restart clock to get the elapsed time from the previous frame
        this->deltaTime = this->getDeltaTime();
            
        if (this->window->hasFocus())
        {
            //Update game
            this->update();
            //Draw game
            this->draw();

            //FPS
            //std::cout << 1 / this->deltaTime << std::endl;
        }
    }
}

void Game::update()
{
    //Update the events
    this->updateEvents();

    //Update the current state
    if (!this->paused)
        this->state->update(this->pressed, this->released, this->tapped, this->clicked, this->unclicked, this->oneHitClicked, this->mousePosView, this->mousePosWindow, this->deltaTime);
    else
    {
        this->pauseState->update(this->pressed, this->released, this->tapped, this->clicked, this->unclicked, this->oneHitClicked, this->mousePosView, this->mousePosWindow, this->state->getCamera().getCenter(), this->deltaTime);
        this->managePauseState();
    }

    //Manage states
    this->manageStates();

    //Update the view
    if (!this->paused)
        this->state->updateView(*this->window, this->deltaTime);
}

void Game::draw()
{
    //Clear
    this->window->clear();

    //Draw the current state
    this->state->draw(*this->window);

    if (this->paused)
        this->pauseState->draw(*this->window);

    //Display
    this->window->display();
}