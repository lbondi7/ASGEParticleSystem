#include "EditorScene.h"
#include <filesystem>

EditorScene::~EditorScene()
{
}

bool EditorScene::init(ASGE::Renderer * renderer, ASGE::Input * input_, std::vector<std::string> file_names)
{
	input = input_;
	scene_ren = renderer;

	renderer->setClearColour(ASGE::COLOURS::BLACK);

	std::string path = "Resources\\Textures";

	{
		for (int i = 0; i <= EXIT; i++)
		{
			menu_buttons[i] = std::unique_ptr<GameObject>(new GameObject());
		}

		int y = 5;
		for (int i = 0; i <= EXIT; i++)
		{
			menu_buttons[i]->addSpriteComponent(renderer, "Resources\\Textures\\button.png");
			menu_buttons[i]->spriteComponent()->getSprite()->width(150);
			menu_buttons[i]->spriteComponent()->getSprite()->height(30);
			menu_buttons[i]->spriteComponent()->getSprite()->xPos(GAME_WIDTH - menu_buttons[i]->spriteComponent()->getSprite()->width() - 5);
			menu_buttons[i]->spriteComponent()->getSprite()->yPos(y);
			y += menu_buttons[i]->spriteComponent()->getSprite()->height() + 5;
		}

		GameObjectVector temp;
		for (int i = 0; i <= ParticleParameters::P_TEXTURE; i++)
		{
			temp.push_back(GameObject());
		}
		parameter_buttons.push_back(temp);
		temp.clear();
		for (int i = 0; i <= EmitterParameters::E_ANGLE; i++)
		{
			temp.push_back(GameObject());
		}
		parameter_buttons.push_back(temp);

		for (int i = 0; i < 2; i++)
		{
			y = 5;
			for (int j = 0; j < parameter_buttons[i].size(); j++)
			{
				parameter_buttons[i][j].addSpriteComponent(renderer, "Resources\\Textures\\button.png");
				parameter_buttons[i][j].spriteComponent()->getSprite()->width(250);
				parameter_buttons[i][j].spriteComponent()->getSprite()->height(30);
				parameter_buttons[i][j].spriteComponent()->getSprite()->xPos(menu_buttons[0]->spriteComponent()->getSprite()->xPos()- parameter_buttons[i][j].spriteComponent()->getSprite()->width() - 5);
				parameter_buttons[i][j].spriteComponent()->getSprite()->yPos(y);
				y += parameter_buttons[i][j].spriteComponent()->getSprite()->height() + 5;
				parameter_buttons[button][j].Active(true);
			}
		}
	}

	{
		FileSystem file;
		if (!file.getTxtFileContent("texturesAvailable"))
		{
			return false;
		}
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			textures.push_back(file.retrieveContent(i));
		}

		if (!file.getTxtFileContent("texturesAvailableUI"))
		{
			return false;
		}
		texture_amount = file.retrieveContentSize();
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			texturez.push_back(GameObject());
		}
		int y = 0;
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			texturez[i].addSpriteComponent(renderer, file.retrieveContent(i));
			texturez[i].setTexture(file.retrieveContent(i));
			float width_multiplier, height_multiplier;
			width_multiplier = texturez[i].spriteComponent()->getSprite()->width() / 100.0f;
			height_multiplier = texturez[i].spriteComponent()->getSprite()->height() / 100.0f;
			texturez[i].spriteComponent()->getSprite()->width(texturez[i].spriteComponent()->getSprite()->width() / width_multiplier);
			texturez[i].spriteComponent()->getSprite()->height(texturez[i].spriteComponent()->getSprite()->height() / height_multiplier);
			texturez[i].spriteComponent()->getSprite()->xPos(parameter_buttons[0][0].spriteComponent()->getSprite()->xPos() - texturez[i].spriteComponent()->getSprite()->width() - 10);
			texturez[i].spriteComponent()->getSprite()->yPos(y);
			y += texturez[i].spriteComponent()->getSprite()->height() + 5;
		}
	}

	{
		FileSystem file;

		if (!file.getTxtFileContent("emitterShapes"))
		{
			return false;
		}
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			emitter_shapes.push_back(GameObject());
		}
		int y = 0;
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			emitter_shapes[i].addSpriteComponent(renderer, file.retrieveContent(i));
			emitter_shapes[i].setTexture(file.retrieveContent(i));
			float width_multiplier, height_multiplier;
			width_multiplier = emitter_shapes[i].spriteComponent()->getSprite()->width() / 100.0f;
			height_multiplier = emitter_shapes[i].spriteComponent()->getSprite()->height() / 100.0f;
			emitter_shapes[i].spriteComponent()->getSprite()->width(emitter_shapes[i].spriteComponent()->getSprite()->width() / width_multiplier);
			emitter_shapes[i].spriteComponent()->getSprite()->height(emitter_shapes[i].spriteComponent()->getSprite()->height() / height_multiplier);
			emitter_shapes[i].spriteComponent()->getSprite()->xPos(parameter_buttons[1][0].spriteComponent()->getSprite()->xPos() - emitter_shapes[i].spriteComponent()->getSprite()->width() - 10);
			emitter_shapes[i].spriteComponent()->getSprite()->yPos(y);
			y += emitter_shapes[i].spriteComponent()->getSprite()->height() + 5;
			if (i == 0)
				emitter_shapes[i].setTag("rectangle");
			else if (i == 1)
				emitter_shapes[i].setTag("circle");
			else if (i == 2)
				emitter_shapes[i].setTag("donut");
		}
	}

	int y = 0;
	for (int i = 0; i < num_of_colours; i++)
	{
		colours_ui[i] = std::unique_ptr<GameObject>(new GameObject());
	}
	for (int i = 0; i < num_of_colours; i++)
	{
		colours_ui[i]->addSpriteComponent(renderer, "Resources\\Textures\\BLANK_TEXTURE.png");
		colours_ui[i]->spriteComponent()->getSprite()->colour(ASGE::COLOURS_ARRAY::COLOUR[i]);
		colours_ui[i]->spriteComponent()->getSprite()->width(50);
		colours_ui[i]->spriteComponent()->getSprite()->height(50);
		colours_ui[i]->spriteComponent()->getSprite()->xPos(parameter_buttons[0][0].spriteComponent()->getSprite()->xPos() - colours_ui[i]->spriteComponent()->getSprite()->width() - 10);
		colours_ui[i]->spriteComponent()->getSprite()->yPos(y);
		y += colours_ui[i]->spriteComponent()->getSprite()->height() + 5;
	}

	for (int i = 0; i < target_colour.size(); i++)
	{
		colours[i] = std::unique_ptr<GameObject>(new GameObject());
	}
	int x = GAME_WIDTH / 2;
	for (int i = 0; i < target_colour.size(); i++)
	{
		colours[i]->addSpriteComponent(renderer, "Resources\\Textures\\BLANK_TEXTURE.png");
		colours[i]->spriteComponent()->getSprite()->colour(target_colour[i]);
		colours[i]->spriteComponent()->getSprite()->width(50);
		colours[i]->spriteComponent()->getSprite()->height(50);
		colours[i]->spriteComponent()->getSprite()->xPos(x);
		x += colours[i]->spriteComponent()->getSprite()->width() + 5;
	}


	//int number_of_files = 0;
	//for (auto const & file : std::experimental::filesystem::directory_iterator(path))
	//{
	//	number_of_files++;
	//}
	//

	emitter_point = std::unique_ptr<GameObject>(new GameObject());
	if (!emitter_point->addSpriteComponent(renderer, "Resources\\Textures\\BLANK_TEXTURE.png"))
	{
		return false;
	}
	emitter_point->spriteComponent()->getSprite()->colour(ASGE::COLOURS::CRIMSON);
	emitter_point->spriteComponent()->getSprite()->width(10.0);
	emitter_point->spriteComponent()->getSprite()->height(10.0);

	emitter.x = 1000;
	emitter.y = 200;
	emitter.length = 100;
	emitter.height = 20;

	particle_system = std::unique_ptr<EditorParticleSystem>(new EditorParticleSystem());
	particle_system->init(scene_ren, input_, density, emission_rate);
	particle_system->updateParticleSystemValues(renderer, density, emission_rate);
	for (int i = 0; i < density; i++)
	{
		particle_system->getParticle(i)->setTexture(texture_name);
		particle_system->getParticle(i)->setDimensions(particle_width, particle_height);
		particle_system->getParticle(i)->setVelocity(velocity);
		particle_system->getParticle(i)->setAngles(max_angle, angle_offset, randomise_angle);
		particle_system->getParticle(i)->setLifetime(max_life_time);
		particle_system->getParticle(i)->setOpacity(target_opacity, opacity_change_rate);
		particle_system->getParticle(i)->setColour(target_colour, colour_change_rate);
		particle_system->getParticle(i)->setEmitterType(emitter_type, donut_width);
		particle_system->getParticle(i)->setEmitterPosDim(emitter.x, emitter.y, emitter.length, emitter.height);
	}

	FloatVector temp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < parameter_names[i].size(); j++)
		{
			for (int k = 0; k < parameter_names[i][j].size(); k++)
			{
				temp.push_back(0.0f);
			}
			parameter_values[i].push_back(temp);
			temp.clear();
		}
	}

	setValues(0);

	return true;
}

Scene::NextScene EditorScene::update(float dt)
{
	if (current_action == EditorScene::Action::CHANGE_TO_MENU)
	{
		current_action = EditorScene::Action::NONE;
		return Scene::MENU_EDITOR;
	}

	counter += dt;
	if (counter > 0.4)
	{
		counter = 0.0;
		show_marker = !show_marker;
	}

	if (debug)
	{
		emitter_point->spriteComponent()->getSprite()->xPos(parameter_values[Buttons::EMITTER][E_POSITION].at(0));
		emitter_point->spriteComponent()->getSprite()->yPos(parameter_values[Buttons::EMITTER][E_POSITION].at(1));
		emitter_point->spriteComponent()->getSprite()->width(parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(0));
		emitter_point->spriteComponent()->getSprite()->height(parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(1));
	}


	if (drag)
	{
		double x_pos, y_pos;
		input->getCursorPos(x_pos, y_pos);

		parameter_values[Buttons::EMITTER][E_POSITION].at(0) = x_pos - x_dif;
		parameter_values[Buttons::EMITTER][E_POSITION].at(1) = y_pos - y_dif;

		emitter_point->spriteComponent()->getSprite()->xPos(parameter_values[Buttons::EMITTER][E_POSITION].at(0));
		emitter_point->spriteComponent()->getSprite()->yPos(parameter_values[Buttons::EMITTER][E_POSITION].at(1));
	}
	else if (!drag)
	{
		particle_system->update(dt);
	}

	if (particle_parameters == P_TEXTURE)
	{
		int y = 0;
		for (int i = 0; i < texturez.size(); i++)
		{
			texturez[i].spriteComponent()->getSprite()->yPos(ui_offset + y);
			y += texturez[i].spriteComponent()->getSprite()->height() + 5;
		}
	}
	else if (particle_parameters == P_COLOURS)
	{
		int y = 0;
		for (int i = 0; i < num_of_colours; i++)
		{
			colours_ui[i]->spriteComponent()->getSprite()->yPos(ui_offset + y);
			y += colours_ui[i]->spriteComponent()->getSprite()->height() + 5;
		}
		int x = GAME_WIDTH / 2;
		for (int i = 0; i < target_colour.size(); i++)
		{
			if (parameter_amount[0] == i)
			{
				colours[i]->spriteComponent()->getSprite()->width(100);
				colours[i]->spriteComponent()->getSprite()->height(100);
			}
			else
			{
				colours[i]->spriteComponent()->getSprite()->width(50);
				colours[i]->spriteComponent()->getSprite()->height(50);
			}
			colours[i]->spriteComponent()->getSprite()->xPos(x);
			x += colours[i]->spriteComponent()->getSprite()->width() + 5;
		}
	}

	for (int i = 0; i <= Buttons::EXIT; i++)
	{
		if (i == button)
			menu_buttons[i]->spriteComponent()->getSprite()->colour(ASGE::COLOURS::PALEGREEN);
		else
			menu_buttons[i]->spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITE);
	}
	if (button < FILENAME)
	{
		for (int i = 0; i < parameter_buttons[button].size(); i++)
		{
			if (button == Buttons::PARTICLE)
			{
				if (i == particle_parameters)
					parameter_buttons[button][i].spriteComponent()->getSprite()->colour(ASGE::COLOURS::PALEGREEN);
				else
					parameter_buttons[button][i].spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITE);
			}
			if (button == Buttons::EMITTER)
			{
				if (i == emitter_parameters)
					parameter_buttons[button][i].spriteComponent()->getSprite()->colour(ASGE::COLOURS::PALEGREEN);
				else
					parameter_buttons[button][i].spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITE);
			}
		}
	}
	if (button == Buttons::PARTICLE)
	{
		if(particle_parameters < ParticleParameters::P_COLOURS)
			parameter_amount[1] = parameter_names[button][particle_parameters].size() - 1;
	}
	else if (button == Buttons::EMITTER)
	{
		if (emitter_parameters > EmitterParameters::E_TYPE)
			parameter_amount[1] = parameter_names[button][emitter_parameters].size() - 1;
	}
	else if (button == Buttons::FILENAME)
	{
		parameter_amount[1] = parameter_names[button][0].size() - 1;
	}
	setValues(1);

	return Scene::NONE;
}

void EditorScene::setValues(int value)
{
	switch (value)
	{
	case 0:
		parameter_values[Buttons::PARTICLE][P_DENSITY].at(0) = density;
		parameter_values[Buttons::PARTICLE][P_EMISSION_RATE].at(0) = emission_rate;
		parameter_values[Buttons::PARTICLE][P_DIMENSIONS].at(0) = particle_width;
		parameter_values[Buttons::PARTICLE][P_DIMENSIONS].at(1) = particle_height;
		parameter_values[Buttons::PARTICLE][P_ANGLES].at(0) = max_angle;
		parameter_values[Buttons::PARTICLE][P_ANGLES].at(1) = angle_offset;
		parameter_values[Buttons::PARTICLE][P_ANGLES].at(2) = randomise_angle;
		parameter_values[Buttons::PARTICLE][P_VELOCITY].at(0) = velocity;
		parameter_values[Buttons::PARTICLE][P_LIFETIME].at(0) = max_life_time;
		parameter_values[Buttons::PARTICLE][P_OPACITY].at(0) = target_opacity[0];
		parameter_values[Buttons::PARTICLE][P_OPACITY].at(1) = target_opacity[1];
		parameter_values[Buttons::PARTICLE][P_OPACITY].at(2) = target_opacity[2];
		parameter_values[Buttons::PARTICLE][P_OPACITY_RATE].at(0) = opacity_change_rate[0];
		parameter_values[Buttons::PARTICLE][P_OPACITY_RATE].at(1) = opacity_change_rate[1];
		parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(0) = colour_change_rate[0];
		parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(1) = colour_change_rate[1];
		parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(2) = colour_change_rate[2];
		parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(3) = colour_change_rate[3];
		parameter_values[Buttons::EMITTER][E_TYPE].at(0) = emitter_type;
		parameter_values[Buttons::EMITTER][E_POSITION].at(0) = emitter.x;
		parameter_values[Buttons::EMITTER][E_POSITION].at(1) = emitter.y;
		parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(0) = emitter.length;
		parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(1) = emitter.height;
		parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(2) = donut_width;
		parameter_values[Buttons::EMITTER][E_ANGLE].at(0) = emitter_angle;

		break;
	case 1:
		density = parameter_values[Buttons::PARTICLE][P_DENSITY].at(0);
		emission_rate = parameter_values[Buttons::PARTICLE][P_EMISSION_RATE].at(0);
		particle_width = parameter_values[Buttons::PARTICLE][P_DIMENSIONS].at(0);
		particle_height = parameter_values[Buttons::PARTICLE][P_DIMENSIONS].at(1);
		max_angle = parameter_values[Buttons::PARTICLE][P_ANGLES].at(0);
		angle_offset = parameter_values[Buttons::PARTICLE][P_ANGLES].at(1);
		randomise_angle = parameter_values[Buttons::PARTICLE][P_ANGLES].at(2);
		velocity = parameter_values[Buttons::PARTICLE][P_VELOCITY].at(0);
		max_life_time = parameter_values[Buttons::PARTICLE][P_LIFETIME].at(0);
		target_opacity[0] = parameter_values[Buttons::PARTICLE][P_OPACITY].at(0);
		target_opacity[1] = parameter_values[Buttons::PARTICLE][P_OPACITY].at(1);
		target_opacity[2] = parameter_values[Buttons::PARTICLE][P_OPACITY].at(2);
		opacity_change_rate[0] = parameter_values[Buttons::PARTICLE][P_OPACITY_RATE].at(0);
		opacity_change_rate[1] = parameter_values[Buttons::PARTICLE][P_OPACITY_RATE].at(1);
		colour_change_rate[0] = parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(0);
		colour_change_rate[1] = parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(1);
		colour_change_rate[2] = parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(2);
		colour_change_rate[3] = parameter_values[Buttons::PARTICLE][P_COLOUR_RATE].at(3);
		emitter.x = parameter_values[Buttons::EMITTER][E_POSITION].at(0);
		emitter.y = parameter_values[Buttons::EMITTER][E_POSITION].at(1);
		emitter.length = parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(0);
		emitter.height = parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(1);
		donut_width = parameter_values[Buttons::EMITTER][E_DIMENSIONS].at(2);
		emitter_angle = parameter_values[Buttons::EMITTER][E_ANGLE].at(0);
		break;														
	}
}

void EditorScene::render(ASGE::Renderer * renderer)
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	if (update_system)
	{
		setValues(1);
		particle_system->updateParticleSystemValues(renderer, density, emission_rate);
		for (int i = 0; i < density; i++)
		{
			particle_system->getParticle(i)->setTexture(texture_name);
			particle_system->getParticle(i)->setDimensions(particle_width, particle_height);
			particle_system->getParticle(i)->setVelocity(velocity);
			particle_system->getParticle(i)->setAngles(max_angle, angle_offset, randomise_angle);
			particle_system->getParticle(i)->setLifetime(max_life_time);
			particle_system->getParticle(i)->setOpacity(target_opacity, opacity_change_rate);
			particle_system->getParticle(i)->setColour(target_colour, colour_change_rate);
			particle_system->getParticle(i)->setEmitterType(emitter_type, donut_width);
			particle_system->getParticle(i)->setEmitterPosDim(emitter.x, emitter.y, emitter.length, emitter.height);
		}
		update_system = false;
	}

	if (drag || (debug == 2 || debug == 3))
	{
		emitter_point->render(renderer);
	}

	particle_system->render(renderer);


	if (debug == 1 || debug == 3)
	{
		std::string line = "";
		line += "Particle Density: " + std::to_string(density);
		line += "\nEmission rate: " + std::to_string(emission_rate);
		line += "\nParticle Dimensions: " + std::to_string(particle_width) + ", " + std::to_string(particle_height);
		line += "\nMax Angle: " + std::to_string(max_angle);
		line += "\nAngle Offset: " + std::to_string(angle_offset);
		line += "\nRandomise Angle: " + std::to_string(randomise_angle);
		line += "\nVelocity: " + std::to_string(velocity);
		line += "\nLifetime: " + std::to_string(max_life_time);
		line += "\nEmitter Position: " + std::to_string(emitter.x) + ", " + std::to_string(emitter.y);
		line += "\nEmitter Dimensions: " + std::to_string(emitter.length) + ", " + std::to_string(emitter.height);
		line += "\nOpacity Over Lifetime: " + std::to_string(target_opacity[0]) + ", " + std::to_string(target_opacity[1]) + ", " + std::to_string(target_opacity[2]);
		line += "\nOpacity Change Rate: " + std::to_string(opacity_change_rate[0]) + ", " + std::to_string(opacity_change_rate[1]);
		line += "\nColourChange Rate: " + std::to_string(colour_change_rate[0]) + ", " + std::to_string(colour_change_rate[1]) + ", " + std::to_string(colour_change_rate[2]) + ", " + std::to_string(colour_change_rate[3]);
		line += "\nTexture: " + texture_name;
		line += "\nFile Name: " + file_name;

		renderer->renderText(line, 0.0, 30.0, 1.0, ASGE::COLOURS::WHITE);
	}

	float x_pos = 1200.0;
	float y_pos = 30.0;

	if (button < Buttons::SAVE)
	{
		std::string line = "";
		if (button < Buttons::FILENAME)
		{
			for (int i = 0; i < parameter_buttons[button].size(); i++)
			{
				parameter_buttons[button][i].render(renderer);
				if (button == Buttons::PARTICLE)
					renderer->renderText(p_btn_names[i], parameter_buttons[button][i].spriteComponent()->getSprite()->xPos() + 5, parameter_buttons[button][i].spriteComponent()->getSprite()->yPos() + (parameter_buttons[button][i].spriteComponent()->getSprite()->height() * 0.75), 1.0, ASGE::COLOURS::BLACK);
				else if (button == Buttons::EMITTER)
					renderer->renderText(e_btn_names[i], parameter_buttons[button][i].spriteComponent()->getSprite()->xPos() + 5, parameter_buttons[button][i].spriteComponent()->getSprite()->yPos() + (parameter_buttons[button][i].spriteComponent()->getSprite()->height() * 0.75), 1.0, ASGE::COLOURS::BLACK);
			}

			if (button == Buttons::PARTICLE)
			{
				if (particle_parameters < ParticleParameters::P_COLOURS)
				{
					for (int i = 0; i < parameter_names[button][particle_parameters].size(); i++)
					{
						line = parameter_names[button][particle_parameters][i];
						if (i == parameter_amount[0])
						{
							if (show_marker)
								renderer->renderText(line + user_input + "_", x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
							else if (!show_marker)
								renderer->renderText(line + user_input, x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
						}
						else
							renderer->renderText(line, x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);

						y_pos += 30;
					}
				}
				else if (particle_parameters == P_COLOURS)
				{
					for (int i = 0; i < num_of_colours; i++)
					{
						colours_ui[i]->render(renderer);
					}
					for (int i = 0; i < 5; i++)
					{
						colours[i]->render(renderer);
					}
				}
				else if (particle_parameters == P_TEXTURE)
				{
					for (int i = 0; i < texture_amount; i++)
					{
						texturez[i].render(renderer);
					}
				}
			}
			else if (button == Buttons::EMITTER)
			{
				if (emitter_parameters != EmitterParameters::E_TYPE)
				{
					for (int i = 0; i < parameter_names[button][emitter_parameters].size(); i++)
					{
						line = parameter_names[button][emitter_parameters][i];
						if (i == parameter_amount[0])
						{
							if (show_marker)
								renderer->renderText(line + user_input + "_", x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
							else if (!show_marker)
								renderer->renderText(line + user_input, x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
						}
						else
							renderer->renderText(line, x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);

						y_pos += 30;
					}
				}
				else if (emitter_parameters == EmitterParameters::E_TYPE)
				{
					for (int i = 0; i < emitter_shapes.size(); i++)
					{
						emitter_shapes[i].render(renderer);
					}
				}
			}
		}
		else if (button == Buttons::FILENAME)
		{
			line = parameter_names[button][0][0];
			if (show_marker)
				renderer->renderText(line + user_input + "_", x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
			else if (!show_marker)
				renderer->renderText(line + user_input, x_pos, y_pos, 1.0, ASGE::COLOURS::WHITE);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		menu_buttons[i]->render(renderer);
		renderer->renderText(m_btn_names[i], menu_buttons[i]->spriteComponent()->getSprite()->xPos() + 5, menu_buttons[i]->spriteComponent()->getSprite()->yPos() + (menu_buttons[i]->spriteComponent()->getSprite()->height() * 0.75), 1.0, ASGE::COLOURS::BLACK);
	}
}

std::string EditorScene::addFilename()
{
	return file_name;
}

void EditorScene::keyHandler(const ASGE::KeyEvent* event)
{
	if (event->action == ASGE::KEYS::KEY_PRESSED)
	{
		if (event->key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_action = EditorScene::Action::CHANGE_TO_MENU;
			pause = false;
			file_name = "";
		}
		else if (event->key == ASGE::KEYS::KEY_ENTER && user_input != "")
		{
			if (button == Buttons::PARTICLE)
			{
				if (particle_parameters < ParticleParameters::P_COLOURS)
				{
					if ((particle_parameters != ParticleParameters::P_OPACITY && particle_parameters != ParticleParameters::P_ANGLES))
					{
						if (std::stof(user_input) > 0)
						{
							parameter_values[button][particle_parameters][parameter_amount[0]] = std::stof(user_input);
							update_system = true;
						}
					}
					else if (particle_parameters == ParticleParameters::P_OPACITY)
					{
						if (std::stof(user_input) >= 0 && std::stof(user_input) <= 1)
						{
							parameter_values[button][particle_parameters][parameter_amount[0]] = std::stof(user_input);
							update_system = true;
						}
					}
					else if (particle_parameters == ParticleParameters::P_ANGLES)
					{
						if (parameter_amount[0] == 2)
						{
							if (std::stoi(user_input) == 0 || std::stoi(user_input) == 1)
							{
								parameter_values[button][particle_parameters][parameter_amount[0]] = std::stoi(user_input);
								update_system = true;
							}
						}
						else
						{
							parameter_values[button][particle_parameters][parameter_amount[0]] = std::stof(user_input);
							update_system = true;
						}
					}
				}
			}
			else if (button == Buttons::EMITTER)
			{
				if (emitter_parameters > EmitterParameters::E_TYPE)
				{
					if (emitter_parameters == EmitterParameters::E_DIMENSIONS)
					{
						if (std::stof(user_input) > 0)
						{
							parameter_values[button][emitter_parameters][parameter_amount[0]] = std::stof(user_input);
							update_system = true;
						}
					}
					else
					{
						parameter_values[button][emitter_parameters][parameter_amount[0]] = std::stof(user_input);
						update_system = true;
					}
				}
			}
			else if (button == Buttons::FILENAME)
			{
				if (user_input != "")
				{
					file_name = user_input;
					update_system = true;
				}
			}
			user_input = "";
		}
		if (event->key == ASGE::KEYS::KEY_UP || event->key == ASGE::KEYS::KEY_DOWN || event->key == ASGE::KEYS::KEY_LEFT || event->key == ASGE::KEYS::KEY_RIGHT) {
			if (event->key == ASGE::KEYS::KEY_DOWN) {
				parameter_amount[0]++;
				if (parameter_amount[0] > parameter_amount[1])
				{
					parameter_amount[0] = 0;
				}
			}
			else if (event->key == ASGE::KEYS::KEY_UP) {
				parameter_amount[0]--;
				if (parameter_amount[0] < 0)
				{
					parameter_amount[0] = parameter_amount[1];
				}
			}
			user_input = "";
		}
		else if (event->key == ASGE::KEYS::KEY_BACKSPACE)
		{
			if (user_input.size() > 0)
			{
				user_input.resize(user_input.size() - 1);
			}
		}
		else if (event->key == ASGE::KEYS::KEY_TAB)
		{
			debug++;
			if (debug > 3)
			{
				debug = 0;
			}
		}
		else if (event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_PERIOD || event->key == ASGE::KEYS::KEY_MINUS)
		{
			if (button == Buttons::PARTICLE)
			{
				if (particle_parameters < ParticleParameters::P_COLOURS)
				{
					if (user_input.size() < 10)
						user_input += event->key;
				}
			}
			else if (button == Buttons::EMITTER)
			{
				if (emitter_parameters > EmitterParameters::E_TYPE)
				{
					if (user_input.size() < 10)
						user_input += event->key;
				}
			}
			else if (button == Buttons::FILENAME)
			{
				if (user_input.size() < 10)
					user_input += event->key;
			}
		}
		else if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
		{
			if (button == Buttons::FILENAME)
			{
				user_input += "_";
			}
		}
		else if (event->mods == 1 && event->key == ASGE::KEYS::KEY_EQUAL)
		{
			if (button == Buttons::FILENAME)
			{
				user_input += "+";
			}
		}
		else if (event->key >= ASGE::KEYS::KEY_A && event->key <= ASGE::KEYS::KEY_Z || event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_MINUS)
		{
			if (button == Buttons::FILENAME)
			{
				if (user_input.size() < 15)
					user_input += event->key;
			}
		}
	}
	if (event->action == ASGE::KEYS::KEY_REPEATED)
	{
		//if (parameters < SAVE)
		//{
		//	if (parameters < COLOURS)
		//	{
		//		if (event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_PERIOD || event->key == ASGE::KEYS::KEY_MINUS)
		//		{
		//			if (user_input.size() < 10)
		//				user_input += event->key;
		//		}
		//	}
		//	if (parameters >= COLOURS)
		//	{
		//		if (event->key >= ASGE::KEYS::KEY_A && event->key <= ASGE::KEYS::KEY_Z || event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_MINUS)
		//		{
		//			if (user_input.size() < 15)
		//				user_input += event->key;
		//		}
		//		if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
		//		{
		//			user_input += "_";
		//		}
		//	}
		//	if (event->key == ASGE::KEYS::KEY_BACKSPACE)
		//	{
		//		if (user_input.size() > 0)
		//		{
		//			user_input.resize(user_input.size() - 1);
		//		}
		//	}
		//}
	}
}

void EditorScene::clickHandler(const ASGE::ClickEvent * event)
{
	if (event->action == ASGE::KEYS::KEY_PRESSED)
	{
		if (event->button == ASGE::KEYS::LEFT_CLICK)
		{
			double x_pos, y_pos;
			input->getCursorPos(x_pos, y_pos);

			int check = 0;
			for (int i = 0; i <= Buttons::EXIT; i++)
			{
				if (menu_buttons[i]->spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
				{
					menuButtonsClicked(i, check);
					break;
				}
			}

			if (check == 0) 
			{
				if (button < Buttons::FILENAME)
				{
					for (int i = 0; i < parameter_buttons[button].size(); i++)
					{
						if (parameter_buttons[button][i].spriteComponent()->getBoundingBox().isInside(x_pos, y_pos) && parameter_buttons[button][i].Active())
						{
							parameterButtonsClicked(i, check);
							break;
						}
					}
				}
				if (check == 0)
				{
					if (button == Buttons::PARTICLE)
					{
						if (particle_parameters == ParticleParameters::P_COLOURS)
						{
							colourButtonsClicked(x_pos, y_pos, check);
						}
						else if (particle_parameters == ParticleParameters::P_TEXTURE)
						{
							textureButtonsClicked(x_pos, y_pos, check);
						}
					}
					else if (button == Buttons::EMITTER)
					{
						if (emitter_parameters == EmitterParameters::E_TYPE)
						{
							for (int i = 0; i < emitter_shapes.size(); i++)
							{
								if (emitter_shapes[i].spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
								{
									emitter_type = i;
									shape = emitter_shapes[i].getTag();
									check = 1;
									update_system = true;
									break;
								}
							}
						}
					}


					if (check == 0)
					{
						x_dif = x_pos - parameter_values[Buttons::EMITTER][E_POSITION].at(0);
						y_dif = y_pos - parameter_values[Buttons::EMITTER][E_POSITION].at(1);
						drag = true;
					}
				}
			}
		}
	}
	else if (event->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (event->button == ASGE::KEYS::LEFT_CLICK)
		{
			if (drag)
			{
				drag = false;
				update_system = true;
			}
		}
	}
}

void EditorScene::colourButtonsClicked(double x_pos, double y_pos, int &check)
{
	for (int i = 0; i < num_of_colours; i++)
	{
		if (colours_ui[i]->spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
		{
			colours[parameter_amount[0]]->spriteComponent()->getSprite()->colour(colours_ui[i]->spriteComponent()->getSprite()->colour());
			target_colour[parameter_amount[0]] = colours_ui[i]->spriteComponent()->getSprite()->colour();
			update_system = true;
			check = 1;
			break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (colours[i]->spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
		{
			parameter_amount[0] = i;
			check = 1;
			break;
		}
	}
}

void EditorScene::textureButtonsClicked(double x_pos, double y_pos, int &check)
{
	for (int i = 0; i < texturez.size(); i++)
	{
		if (texturez[i].spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
		{
			texture_name = texturez[i].getTexture();
			update_system = true;
			check = 1;
			break;
		}
	}
}

void EditorScene::parameterButtonsClicked(int i, int &check)
{
	if (button == Buttons::PARTICLE)
	{
		particle_parameters = (ParticleParameters)i;
	}
	else if (button == Buttons::EMITTER)
	{
		emitter_parameters = (EmitterParameters)i;
	}
	parameter_amount[0] = 0;
	check = 1;
}

void EditorScene::menuButtonsClicked(int i, int &check)
{
	button = (Buttons)i;
	if (button < Buttons::FILENAME)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < parameter_buttons[j].size(); k++)
			{
				parameter_buttons[button][j].Active(false);
			}
		}
		for (int j = 0; j < parameter_buttons[button].size(); j++)
		{
			parameter_buttons[button][j].Active(true);
		}
	}
	if (button == Buttons::SAVE)
	{
		if (file_name != "")
		{
			FileSystem file;
			file.particleSystemBuffer(density, emission_rate);
			file.textureBuffer(texture_name);
			file.dimensionsBuffer(particle_width, particle_height);
			file.velocitysBuffer(velocity);
			file.directionBuffer(max_angle, angle_offset, randomise_angle);
			file.lifetimeBuffer(max_life_time);
			file.opacityBuffer(target_opacity, opacity_change_rate);
			file.colourBuffer(target_colour, colour_change_rate);
			file.emitterTypeBuffer(shape, emitter_type);
			file.emitterPositionBuffer(emitter.x, emitter.y);
			file.emitterDimensionsBuffer(emitter.length, emitter.height, donut_width);
			if (file.createFile(file_name))
			{
				current_action = Action::CHANGE_TO_MENU;
				particle_parameters = ParticleParameters::P_DENSITY;
				emitter_parameters = EmitterParameters::E_TYPE;
				button = Buttons::PARTICLE;
			}
		}
	}
	else if (button == Buttons::EXIT)
	{
		current_action = Action::CHANGE_TO_MENU;
		particle_parameters = ParticleParameters::P_DENSITY;
		emitter_parameters = EmitterParameters::E_TYPE;
		button = Buttons::PARTICLE;
	}
	parameter_amount[0] = 0;
	check = 1;
}

void EditorScene::scrollHandler(const ASGE::ScrollEvent * event)
{

	if (event->yoffset == ASGE::KEYS::KEY_PRESSED)
	{
		ui_offset += 50;
	}
	else if (event->yoffset != ASGE::KEYS::KEY_PRESSED)
	{
		ui_offset -= 50;
	}

}
