#include "SimulationScene.h"

SimulationScene::~SimulationScene()
{
	//input->unregisterCallback(0);
	//key_press = false;
}

bool SimulationScene::init(ASGE::Renderer * renderer, ASGE::Input* input_, std::vector<std::string> file_names)
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);


	input = input_;
	g_renderer = renderer;

	srand(time(NULL));

	file_name = file_names;
	particle_systems_amount = file_name.size();
	for (int i = 0; i < file_name.size(); i++)
	{
		particle_system.push_back(new ParticleSystem());
		particle_system[i]->init(renderer, input_, file_name[i], particle_systems_amount);
	}

	return true;
}

Scene::NextScene SimulationScene::update(float dt)
{
	if (current_action == SimulationScene::Action::CHANGE_TO_MENU)
	{
		//for (int i = 0; i < particle_systems_amount; i++)
		//{
		//	particle_system.pop_back();
		//}
		current_action = SimulationScene::Action::NONE;
		return Scene::MENU_SIM;
	}

	if (pause)
	{
		delay -= dt;
		if (delay <= 0)
		{
			delay = 0.5f;
			pause = false;
		}
	}

	if (drag)
	{
		//double x_pos, y_pos;
		input->getCursorPos(x_dif[1], y_dif[1]);
		x_dif[2] = x_dif[1] - x_dif[0];
		y_dif[2] = y_dif[1] - y_dif[0];
		//p_system_offset[sel_part_sys]->at(0) = x_pos - 
		//particle_system[sel_part_sys]->updateParticleSystemPos(x_pos, y_pos);
	}

	if (new_particle_system)
	{
		generateParticleSystem(g_renderer, input);
	}

	for (int i = 0; i < particle_systems_amount; i++)
	{
		particle_system[i]->update(dt, sel_part_sys, x_dif[2], y_dif[2]);
	}

	return Scene::NONE;
}

void SimulationScene::render(ASGE::Renderer * renderer)
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	for (int i = 0; i < particle_systems_amount; i++)
	{
		particle_system[i]->render(renderer);
	}
	renderer->renderText(user_input, GAME_WIDTH * 0.4, 30, 2.0, ASGE::COLOURS::WHITE);
	renderer->renderText(std::to_string(sel_part_sys), GAME_WIDTH * 0.5, 60, 2.0, ASGE::COLOURS::WHITE);
	std::string list_of_systems = "Available Systems:";
	for (int i = 0; i < file_name.size(); i++)
	{
		list_of_systems += "\n" + file_name[i];
	}
	renderer->renderText(list_of_systems, 5.0f, 20.0f, 1.0, ASGE::COLOURS::WHITE);
}

std::string SimulationScene::addFilename()
{
	return std::string();
}

void SimulationScene::keyHandler(const ASGE::KeyEvent* event)
{
	if (event->action == ASGE::KEYS::KEY_PRESSED)
	{
		if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
		{
			user_input += "_";
		}
		else if (event->key >= ASGE::KEYS::KEY_A && event->key <= ASGE::KEYS::KEY_Z || event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_MINUS)
		{
			user_input += event->key;
		}
		if (event->key == ASGE::KEYS::KEY_BACKSPACE)
		{
			if (user_input.length() > 0)
			{
				user_input.resize(user_input.size() - 1);
			}
		}
		if (event->key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_action = SimulationScene::Action::CHANGE_TO_MENU;
		}
		if (event->key == ASGE::KEYS::KEY_ENTER)
		{
			//if (num_of_systems < particle_systems_amount)
			//{
			//	if (particle_system[num_of_systems]->setParticles(user_input, g_renderer))
			//	{
			//		particle_system[num_of_systems]->setActive(true);
			//		if (num_of_systems > 0)
			//			pause = true;

			for (int i = 0; i < particle_systems_amount; i++)
			{
				if (particle_system[i]->systemName() == user_input && !particle_system[i]->isActive())
				{
					particle_system[i]->setActive(true);
				}
			}
			user_input = "";
		}
		if (event->key == ASGE::KEYS::KEY_DELETE)
		{

			for (int i = 0; i < particle_systems_amount; i++)
			{
				if (particle_system[i]->systemName() == user_input && particle_system[i]->isActive())
				{
					particle_system[i]->setActive(false);
					user_input = "";
				}
			}
		}
	}
}

void SimulationScene::clickHandler(const ASGE::ClickEvent* event)
{
	if (event->action != ASGE::KEYS::KEY_RELEASED)
	{
		if (event->button == 1)
		{
			//double x_pos, y_pos;
			input->getCursorPos(x_dif[0], y_dif[0]);
			//particle_system[sel_part_sys]->setDifference(x_pos, y_pos);
			drag = true;
		}
	}
	if (event->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (event->button == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				x_dif[i] = 0.0;
				y_dif[i] = 0.0;
			}
			drag = false;
		}
	}
}

void SimulationScene::scrollHandler(const ASGE::ScrollEvent* event)
{
	if (event->yoffset == ASGE::KEYS::KEY_PRESSED)
	{
		sel_part_sys++;
		if (sel_part_sys > particle_systems_amount - 1)
		{
			sel_part_sys = 0;
		}
	}
	if (event->yoffset != ASGE::KEYS::KEY_PRESSED)
	{
		sel_part_sys--;
		if (sel_part_sys < 0)
		{
			sel_part_sys = particle_systems_amount - 1;
		}
	}
}

void SimulationScene::generateParticleSystem(ASGE::Renderer* renderer, ASGE::Input* input_)
{
	FileSystem file;
	if (file.getTxtFileContent(user_input))
	{
		particle_systems_amount++;
		ParticleSystem* part = new ParticleSystem();
		particle_system.push_back(part);
		particle_system[particle_systems_amount - 1]->init(renderer, input, user_input, particle_systems_amount - 1);
		user_input = "";
	}
	new_particle_system = false;
}

void SimulationScene::destoryParticleSystem()
{
	//particle_system.pop_back();
	particle_systems_amount--;
}
