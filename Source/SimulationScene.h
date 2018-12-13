#pragma once

#pragma once
#include "Scene.h"
#include "ParticleSystem.h"

class SimulationScene :
	public Scene
{
public:
	SimulationScene() = default;
	virtual ~SimulationScene();

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

	int key_handler_id = -1;
	int click_handler_id = -1;
	int scroll_handler_id = -1;

	enum Action
	{
		CHANGE_TO_MENU,
		NONE
	};

	Action current_action = NONE;

	std::vector<ParticleSystem*> particle_system;
	std::vector<std::string> file_name;

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
};