#pragma once
#include "Scene.h"
#include "EditorParticleSystem.h"

class EditorScene :
	public Scene
{
public:
	EditorScene() = default;
	~EditorScene();

	bool init(ASGE::Renderer* renderer, ASGE::Input* input, std::vector<std::string> file_names) override;
	Scene::NextScene update(float dt) override;
	void render(ASGE::Renderer* renderer) override;
	std::string addFilename() override;
	void keyHandler(const ASGE::KeyEvent* event) override;
	void clickHandler(const ASGE::ClickEvent* event) override;
	void scrollHandler(const ASGE::ScrollEvent* event) override;

private:
	void setValues(int value);
	void colourButtonsClicked(double x_pos, double y_pos, int &check);
	void textureButtonsClicked(double x_pos, double y_pos, int &check);
	void parameterButtonsClicked(int i, int &check);
	void menuButtonsClicked(int i, int &check);

	ASGE::Input* input = nullptr;
	ASGE::Renderer * scene_ren = nullptr;

	enum Action
	{
		CHANGE_TO_MENU,
		NONE
	};

	Action current_action = NONE;

	using GameObjectVector = std::vector<GameObject>;
	using GameObjectPointer = std::unique_ptr<GameObject>;
	using FloatVector = std::vector<float>;
	using String2DVector = std::vector<std::vector<std::string>>;
	GameObjectVector emitter_shapes;
	GameObjectVector texturez;
	std::vector<GameObjectVector> parameter_buttons;
	GameObjectPointer menu_buttons[5];
	GameObjectPointer colours[5]{ nullptr };
	GameObjectPointer colours_ui[146]{ nullptr };
	GameObjectPointer emitter_point = nullptr;
	int num_of_colours = 146;
	std::unique_ptr<EditorParticleSystem> particle_system = nullptr;
	std::vector<std::string> textures;

	bool pause = false;

	enum ParticleParameters {
		P_DENSITY = 0,
		P_EMISSION_RATE = 1,
		P_DIMENSIONS = 2,
		P_ANGLES = 3,
		P_VELOCITY = 4,
		P_LIFETIME = 5,
		P_OPACITY = 6,
		P_OPACITY_RATE = 7,
		P_COLOUR_RATE = 8,
		P_COLOURS = 9,
		P_TEXTURE = 10,
	};

	ParticleParameters particle_parameters = P_DENSITY;

	enum EmitterParameters {
		E_TYPE = 0,
		E_POSITION = 1,
		E_DIMENSIONS = 2,
		E_ANGLE = 3,
	};

	EmitterParameters emitter_parameters = E_TYPE;

	enum Buttons {
		PARTICLE = 0,
		EMITTER = 1,
		FILENAME = 2,
		SAVE = 3,
		EXIT = 4
	};

	Buttons button = PARTICLE;

	String2DVector parameter_names[3]{ { { "Particle Density: " },
	{ "Emission Rate: " },
	{ "Particle Width: ", "Particle Height: " },
	{ "Max Angle: ", "Angle Offset: ", "Randomise Angle: " },
	{ "Velocity: " },
	{ "Life Time: " },
	{ "Start Opacity: ","Mid Opacity: ","End Opacity: " },
	{ "Opacity Change Rate 1:", "Opacity Change Rate 2:" },
	{ "Colour Change Rate 1:", "Colour Change Rate 2:", "Colour Change Rate 3:", "Colour Change Rate 4: " } },

	{ { " " },
	{ "Emitter Xpos: ", "Emitter Ypos: " },
	{ "Emitter Width: ", "Emitter Height: ", "Donut Width: " },
	{ "Max Angle: ", "Angle Offset: " } },

	{ { "Filename: " } } };

	std::vector<FloatVector> parameter_values[2];

	std::string m_btn_names[5]{ "Particle","Emitter","File Name","Save","Exit" };
	std::string p_btn_names[11]{ "Density","Emission Rate","Dimensions","Angle","Velocity","Lifetime","Opacity", "Opacity Change Rate","Colour Change Rate" , "Colours" , "Texture" };
	std::string e_btn_names[4]{ "Type","Position","Dimensions","Angle"};
	int parameter_amount[2]{ 0, 0 };
	std::string user_input = "";

	//particle parameters
	std::string texture_name = "Resources\\Textures\\PARTICLE.png";
	int density = 2000;
	float emission_rate = 1000.0f;
	float particle_width = 20.0f;
	float particle_height = 20.0f;
	float max_angle = 20.0f;
	float angle_offset = 0.0f;
	bool randomise_angle = false;
	float velocity = 0.0f;
	float max_life_time = 1.0f;
	std::vector<float> target_opacity{ 1.0f, 1.0f, 1.0f };
	std::vector<float> opacity_change_rate{ 10.0f, 1.0f };
	std::vector<ASGE::Colour> target_colour{ ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE };
	std::vector<float> colour_change_rate{ 1.0f, 1.0f, 1.0f, 1.0f };

	//emitter parameters
	int emitter_type = 0;
	float donut_width = 50.0f;
	rect emitter;
	float emitter_angle = 0.0f;
	std::string shape = "rectangle";

	//file
	std::string file_name = "";

	float counter = 0.0f;
	bool show_marker = true;
	bool drag = false;
	float x_dif = 0.0f, y_dif = 0.0f;
	int texture_amount = 0;
	float ui_offset = 0.0f;
	bool update_system = false;
	int debug = 1;
};
