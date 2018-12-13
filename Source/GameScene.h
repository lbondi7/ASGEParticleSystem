#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "Constants.h"

class GameScene :
	public Scene
{
public:
	GameScene() = default;
	virtual ~GameScene();

	virtual bool init(ASGE::Renderer* renderer, ASGE::Input* input, std::vector<std::string> file_names) override;
	virtual Scene::NextScene update(float dt) override;
	virtual void render(ASGE::Renderer* renderer) override;
	virtual std::string addFilename() override;
	virtual void keyHandler(const ASGE::KeyEvent* event) override;
	virtual void clickHandler(const ASGE::ClickEvent* event) override;
	virtual void scrollHandler(const ASGE::ScrollEvent* event) override;


	void generateParticleSystem(ASGE::Renderer * renderer, ASGE::Input * input);

	void destoryParticleSystem();

private:
	ASGE::Input* input = nullptr;
	ASGE::Renderer* g_renderer = nullptr;

	enum Action
	{
		CHANGE_TO_MENU,
		NONE
	};

	Action current_action = NONE;

	std::vector<ParticleSystem*> particle_system;
	std::vector<std::string> file_name;

	std::unique_ptr<GameObject> player = nullptr;
	std::unique_ptr<GameObject> platforms[PLATFORM_AMOUNT]{ nullptr };

	bool pause = false;
	float delay = 0.5f;
	bool drag = false;
	double x_dif[3], y_dif[3];
	bool key_press = false;
	int particle_systems_amount = 5;
	int num_of_systems = 0;
	bool new_particle_system = false;
	int sel_part_sys = 0;
	float dif[2];
	std::string user_input = "";
	int move_objects = 0;
	float force = 0.0f;
	float gravity = 9.8f;
	bool falling = true;
	bool hit_object = false;
};