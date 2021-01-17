#ifndef STATE_H
#define STATE_H

class Camera;
class Button;

enum States { Main = 1, Play, Settings, Network, LevelChooser, Pause };

class State
{
protected:
	//Variables
	Camera camera;

	std::vector<Label> labels;
	std::vector<Button> buttons;
	std::vector<TextInput> inputs;
	std::vector<ComboBox> comboboxes;
	std::vector<Slider> sliders;
	std::vector<DropBox> dropboxes;

	States state;

public:
	//Constructors/Destructors
	State();
	State(const States& state, const float& width, const float& height);
	virtual ~State();

	//Accessors
	const States getState() const;

	virtual Camera& getCamera();

	const std::vector<Label> getLabels() const;
	const std::vector<Button> getButtons() const;
	const std::vector<TextInput> getInputs() const;
	const std::vector<ComboBox> getComboboxes() const;
	const std::vector<Slider> getSliders() const;
	const std::vector<DropBox> getDropboxes() const;

	//Functions
	virtual void configure();
	virtual void configureLabels();
	virtual void configureButtons();
	virtual void configureInputs();
	virtual void configureComboboxes();
	virtual void configureSliders();
	virtual void configureDropboxes();

	virtual void update(std::map<std::string, sf::Keyboard::Key> pressed,
		std::map<std::string, sf::Keyboard::Key> released,
		std::map<std::string, sf::Keyboard::Key> tapped,
		std::map<std::string, sf::Mouse::Button> clicked, 
		std::map<std::string, sf::Mouse::Button> uncliked, 
		std::map<std::string, sf::Mouse::Button> one_hit_click,
		sf::Vector2i mouse_pos_view,
		sf::Vector2f mouse_pos_window,
		const float deltatime);

	virtual void updateView(sf::RenderWindow& window, const float& deltatime);
	virtual void draw(sf::RenderWindow& window);
};

#endif // !STATE_H