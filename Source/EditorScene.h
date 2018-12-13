#pragma once
#include "Scene.h"
#include "EditorParticleSystem.h"

class EditorScene :
	public Scene
{
public:
	EditorScene() = default;
	virtual ~EditorScene();

	virtual bool init(ASGE::Renderer* renderer, ASGE::Input* input, std::vector<std::string> file_names) override;
	virtual Scene::NextScene update(float dt) override;
	virtual void render(ASGE::Renderer* renderer) override;
	virtual std::string addFilename() override;
	virtual void keyHandler(const ASGE::KeyEvent* event) override;
	virtual void clickHandler(const ASGE::ClickEvent* event) override;
	virtual void scrollHandler(const ASGE::ScrollEvent* event) override;

	std::string displayColour(float red, float green, float blue);

	bool changeColour(std::string colour, int para);

private:
	void setValues(int value);


	ASGE::Input* input = nullptr;
	ASGE::Renderer * scene_ren = nullptr;

	enum Action
	{
		CHANGE_TO_MENU,
		NONE
	};

	Action current_action = NONE;

	std::unique_ptr<EditorParticleSystem> particle_system = nullptr;
	std::unique_ptr<GameObject> emitter_point = nullptr;
	std::unique_ptr<GameObject> objects = nullptr;
	std::vector<GameObject> texturez;
	std::vector<GameObject> buttons;
	std::unique_ptr<GameObject> colours[5]{ nullptr };
	std::unique_ptr<GameObject> colours_ui[146]{ nullptr };
	int num_of_colours = 146;
	std::vector<std::string> textures;

	bool pause = false;

	std::string user_input = " ";
	std::vector<std::vector<std::string>> parameter_names{ { "Particle Density: " },
	{ "Emission Rate: " },
	{ "Particle Width: ", "Particle Height: " },
	{ "Max Angle: ", "Angle Offset: ", "Randomise Angle: " },
	{ "Velocity: " },
	{ "Life Time: " },
	{ "Emitter Xpos: ","Emitter Ypos: ", "Emitter Length: ", "Emitter Height: " },
	{ "Start Opacity: ","Mid Opacity: ","End Opacity: " },
	{ "Opacity Change Rate 1:", "Opacity Change Rate 2:" },
	{ "Colour Change Rate 1:", "Colour Change Rate 2:", "Colour Change Rate 3:", "Colour Change Rate 4: " },
	{ "Colour 1:", "Colour 2:", "Colour 3:", "Colour 4:", "Colour 5:" },
	{ "Texture: " },
	{ "File Name: " } };

	std::vector<float> parameter_values [11];

	enum Parameters {
		DENSITY = 0,
		EMISSION_RATE = 1,
		DIMENSIONS = 2,
		ANGLES = 3,
		VELOCITY = 4,
		LIFETIME = 5,
		EMITTER = 6,
		OPACITY = 7,
		OPACITY_RATE = 8,
		COLOUR_RATE = 9,
		COLOURS = 10,
		TEXTURE = 11,
		FILENAME = 12,
		SAVE = 13,
		EXIT = 14
	};

	std::string button_names[16]{ "Density","Emission Rate","Particle Dimensions","Angle","Velocity","Life Time", "Emitter","Opacity", "Opacity Change Rate","Colour Change Rate" , "Colours" , "Texture" ,"File Name","Save","Exit" };

	Parameters parameters = DENSITY;
	int parameter_amount[2]{ 0, 0 };
	int size_of_vector[SAVE]{ 0, 0, 1, 2, 0, 0, 3, 2, 1, 3, 4, 0, 0 };

	//particle parameters
	int density = 200;
	float emission_rate = 5;
	float particle_width = 1.0f;
	float particle_height = 20.0f;
	float max_angle = 20.0f;
	float angle_offset = 0.0f;
	bool randomise_angle = false;
	float velocity = 300.0f;
	float max_life_time = 1.0f;
	std::vector<float> target_opacity{ 1.0f, 1.0f, 1.0f };
	std::vector<float> opacity_change_rate{ 10.0f, 1.0f };
	std::vector<ASGE::Colour> target_colour{ ASGE::COLOURS::YELLOW, ASGE::COLOURS::ORANGE, ASGE::COLOURS::RED, ASGE::COLOURS::BLUE, ASGE::COLOURS::GREEN };
	std::vector<float> colour_change_rate{ 1.0f, 1.0f, 1.0f, 1.0f };
	rect emitter;
	std::string file_name = "";
	std::string texture_name = "Resources\\Textures\\PARTICLE.png";

	float counter = 0.0f;
	bool show_marker = true;
	bool drag = false;
	float x_dif = 0.0f, y_dif = 0.0f;
	int texture_amount = 0;
	float ui_offset = 0.0f;
	bool update_system = false;
	int debug = 1;
};
