#include "GameScene.h"

GameScene::~GameScene()
{

}

bool GameScene::init(ASGE::Renderer * renderer, ASGE::Input* input_, std::vector<std::string> file_names)
{
	renderer->setClearColour(ASGE::COLOURS::RED);
	input = input_;
	file_name = file_names;
	particle_systems_amount = file_name.size();
	for (int i = 0; i < file_name.size(); i++)
	{
		particle_system.push_back(new ParticleSystem());
		particle_system[i]->init(renderer, input_, file_name[i], particle_systems_amount);
	}

	for (int i = 0; i < PLATFORM_AMOUNT; i++)
	{
		platforms[i] = std::unique_ptr<GameObject>(new GameObject());
	}
	int x = 0;
	for (int i = 0; i < PLATFORM_AMOUNT; i++)
	{
		platforms[i]->setTag("Ground");
		if (i % 4 == 0 && i != 0)
		{
			platforms[i]->setTag("Platform");
		}

		if (platforms[i]->getTag() == "Ground")
		{
			if (!platforms[i]->addSpriteComponent(renderer, "Resources\\Textures\\dirtMid.png"))
			{
				return false;
			}
			platforms[i]->spriteComponent()->getSprite()->yPos(GAME_HEIGHT - platforms[i]->spriteComponent()->getSprite()->height());
		}
		else if (platforms[i]->getTag() == "Platform")
		{
			if (!platforms[i]->addSpriteComponent(renderer, "Resources\\Textures\\planetHalf_mid.png"))
			{
				return false;
			}
			platforms[i]->spriteComponent()->getSprite()->yPos(700);
		}
		platforms[i]->spriteComponent()->getSprite()->xPos(x);
		x += platforms[i]->spriteComponent()->getSprite()->width();
	}

	player = std::unique_ptr<GameObject>(new GameObject());
	if (!player->addSpriteComponent(renderer, "Resources\\Textures\\stoneMid.png"))
	{
		return false;
	}
	player->spriteComponent()->spriteCenter(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	player->spriteComponent()->getSprite()->width(50);
	player->spriteComponent()->getSprite()->height(50);


	return true;
}

Scene::NextScene GameScene::update(float dt)
{
	if (current_action == GameScene::Action::CHANGE_TO_MENU)
	{
		current_action = GameScene::Action::NONE;
		return Scene::MENU_GAME;
	}

	if (falling)
	{
		force += (gravity * 50) *  dt;
		player->spriteComponent()->getSprite()->yPos(player->spriteComponent()->getSprite()->yPos() + (force * dt));
	}

	for (int i = 0; i < PLATFORM_AMOUNT; i++)
	{
		if (player->spriteComponent()->getBoundingBox().isInside(platforms[i]->spriteComponent()->getBoundingBox()) &&
			player->spriteComponent()->getBoundingBox().isInside(platforms[i]->spriteComponent()->bBT()))
		{
			falling = false;
			hit_object = true;
			player->spriteComponent()->getSprite()->yPos(platforms[i]->spriteComponent()->getSprite()->yPos() - player->spriteComponent()->getSprite()->height());
		}
		else
		{
			falling = true;
			if (hit_object)
			{
				hit_object = false;
				force = 0;
			}
		}
	}

	for (int j = 0; j < particle_system.size(); j++)
	{
		for (int k = 0; k < particle_system[j]->getParticleAmount(); k++)
		{
			for (int i = 0; i < PLATFORM_AMOUNT; i++)
			{
				if (particle_system[j]->getParticle(k)->spriteComponent()->getBoundingBox().isInside(platforms[i]->spriteComponent()->getBoundingBox()))
				{
					particle_system[j]->getParticle(k)->resetParticle();
				}
			}

			if (particle_system[j]->getParticle(k)->spriteComponent()->getBoundingBox().isInside(player->spriteComponent()->getBoundingBox()))
			{
				particle_system[j]->getParticle(k)->resetParticle();
			}
		}
	}

	if (move_objects == 1)
	{
		for (int i = 0; i < PLATFORM_AMOUNT; i++)
		{
			platforms[i]->spriteComponent()->getSprite()->xPos(platforms[i]->spriteComponent()->getSprite()->xPos() + (500 * dt));
		}
	}
	else if (move_objects == -1)
	{
		for (int i = 0; i < PLATFORM_AMOUNT; i++)
		{
			platforms[i]->spriteComponent()->getSprite()->xPos(platforms[i]->spriteComponent()->getSprite()->xPos() - (500 * dt));
		}
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
	else if (drag)
	{
		//double x_pos, y_pos;
		input->getCursorPos(x_dif[1], y_dif[1]);
		x_dif[2] = x_dif[1] - x_dif[0];
		y_dif[2] = y_dif[1] - y_dif[0];
		//p_system_offset[sel_part_sys]->at(0) = x_pos - 
		//particle_system[sel_part_sys]->updateParticleSystemPos(x_pos, y_pos);
	}

	for (int i = 0; i < particle_systems_amount; i++)
	{
		particle_system[i]->update(dt, sel_part_sys, x_dif[2], y_dif[2]);
	}

	return Scene::NONE;
}

void GameScene::render(ASGE::Renderer * renderer)
{

	//if (new_particle_system)
	//{
	//	generateParticleSystem(renderer, input);
	//}

	renderer->setClearColour(ASGE::COLOURS::BLACK);
	for (int i = 0; i < particle_systems_amount; i++)
	{
		particle_system[i]->render(renderer);
	}
	player->render(renderer);
	for (int i = 0; i < PLATFORM_AMOUNT; i++)
	{
		platforms[i]->render(renderer);
	}
	renderer->renderText(user_input, GAME_WIDTH * 0.4, 30, 2.0, ASGE::COLOURS::WHITE);
	//renderer->renderText(std::to_string(sel_part_sys), GAME_WIDTH * 0.5, 60, 2.0, ASGE::COLOURS::WHITE);
	renderer->renderText(std::to_string(key_press), GAME_WIDTH * 0.5, 60, 2.0, ASGE::COLOURS::WHITE);
	std::string list_of_systems = "Available Systems:";
	for (int i = 0; i < file_name.size(); i++)
	{
		list_of_systems += "\n" + file_name[i];
	}
	renderer->renderText(list_of_systems, 5.0f, 20.0f, 1.0, ASGE::COLOURS::WHITE);
}

std::string GameScene::addFilename()
{
	return std::string();
}

void GameScene::keyHandler(const ASGE::KeyEvent* event)
{
	if (event->action == ASGE::KEYS::KEY_PRESSED)
	{
		if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
		{
			user_input += "_";
		}
		else if (event->mods == 1 && event->key == ASGE::KEYS::KEY_EQUAL)
		{
			user_input += "+";
		}
		else if (event->key >= ASGE::KEYS::KEY_A && event->key <= ASGE::KEYS::KEY_Z || event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_MINUS)
		{
			user_input += event->key;
		}
		else if (event->key == ASGE::KEYS::KEY_BACKSPACE)
		{
			if (user_input.length() > 0)
			{
				user_input.resize(user_input.size() - 1);
			}
		}
		else if (event->key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_action = GameScene::Action::CHANGE_TO_MENU;
		}
		else if (event->key == ASGE::KEYS::KEY_ENTER)
		{
			for (int i = 0; i < particle_systems_amount; i++)
			{
				if (particle_system[i]->systemName() == user_input && !particle_system[i]->isActive())
				{
					particle_system[i]->setActive(true);
				}
			}
			user_input = "";
		}
		else if (event->key == ASGE::KEYS::KEY_DELETE)
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

		if (event->key == ASGE::KEYS::KEY_RIGHT)
		{
			move_objects = -1;
		}
		else if (event->key == ASGE::KEYS::KEY_LEFT)
		{
			move_objects = 1;
		}
		else if (event->key == ASGE::KEYS::KEY_UP)
		{
			falling = true;
			force = -500.0f;
			hit_object = false;
			player->spriteComponent()->getSprite()->yPos(player->spriteComponent()->getSprite()->yPos() - 3);
		}
	}
	else if (event->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (event->key == ASGE::KEYS::KEY_RIGHT)
		{
			move_objects = 0;
		}
		else if (event->key == ASGE::KEYS::KEY_LEFT)
		{
			move_objects = 0;
		}
	}
}

void GameScene::clickHandler(const ASGE::ClickEvent* event)
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

void GameScene::scrollHandler(const ASGE::ScrollEvent* event)
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

void GameScene::generateParticleSystem(ASGE::Renderer* renderer, ASGE::Input* input_)
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

void GameScene::destoryParticleSystem()
{
	//particle_system.pop_back();
	particle_systems_amount--;
}
