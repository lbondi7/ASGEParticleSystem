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
			buttons.push_back(GameObject());
		}

		int y = 5;
		for (int i = 0; i <= EXIT; i++)
		{
			buttons[i].addSpriteComponent(renderer, "Resources\\Textures\\BLANK_TEXTURE.png");
			buttons[i].spriteComponent()->getSprite()->width(250);
			buttons[i].spriteComponent()->getSprite()->height(30);
			buttons[i].spriteComponent()->getSprite()->xPos(GAME_WIDTH - buttons[i].spriteComponent()->getSprite()->width() - 10);
			buttons[i].spriteComponent()->getSprite()->yPos(y);
			y += buttons[i].spriteComponent()->getSprite()->height() + 5;
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
			texturez[i].spriteComponent()->getSprite()->xPos(buttons[0].spriteComponent()->getSprite()->xPos() - texturez[i].spriteComponent()->getSprite()->width() - 10);
			texturez[i].spriteComponent()->getSprite()->yPos(y);
			y += texturez[i].spriteComponent()->getSprite()->height() + 5;
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
		colours_ui[i]->spriteComponent()->getSprite()->xPos(buttons[0].spriteComponent()->getSprite()->xPos() - colours_ui[i]->spriteComponent()->getSprite()->width() - 10);
		colours_ui[i]->spriteComponent()->getSprite()->yPos(y);
		y += colours_ui[i]->spriteComponent()->getSprite()->height() + 5;
	}

	for (int i = 0; i <= size_of_vector[COLOURS]; i++)
	{
		colours[i] = std::unique_ptr<GameObject>(new GameObject());
	}
	int x = GAME_WIDTH / 2;
	for (int i = 0; i <= size_of_vector[COLOURS]; i++)
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
	emitter.length = 500;
	emitter.height = 20;

	particle_system = std::unique_ptr<EditorParticleSystem>(new EditorParticleSystem());
	particle_system->init(scene_ren, input_, density, emission_rate);
	particle_system->updateParticleSystemValues(renderer,
		texture_name,
		density,
		emission_rate,
		particle_width, particle_height,
		max_angle, angle_offset, randomise_angle,
		velocity,
		max_life_time,
		emitter.x, emitter.y, emitter.length, emitter.height,
		target_opacity, opacity_change_rate,
		target_colour, colour_change_rate);

	for (int i = 0; i < COLOURS; i++)
	{
		for (int j = 0; j <= size_of_vector[i]; j++)
		{
			parameter_values[i].push_back(0.0f);
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
		emitter_point->spriteComponent()->getSprite()->xPos(parameter_values[EMITTER].at(0));
		emitter_point->spriteComponent()->getSprite()->yPos(parameter_values[EMITTER].at(1));
		emitter_point->spriteComponent()->getSprite()->width(parameter_values[EMITTER].at(2));
		emitter_point->spriteComponent()->getSprite()->height(parameter_values[EMITTER].at(3));
	}


	if (drag)
	{
		double x_pos, y_pos;
		input->getCursorPos(x_pos, y_pos);

		parameter_values[EMITTER].at(0) = x_pos - x_dif;
		parameter_values[EMITTER].at(1) = y_pos - y_dif;

		emitter_point->spriteComponent()->getSprite()->xPos(parameter_values[EMITTER].at(0));
		emitter_point->spriteComponent()->getSprite()->yPos(parameter_values[EMITTER].at(1));
		emitter_point->spriteComponent()->getSprite()->width(parameter_values[EMITTER].at(2));
		emitter_point->spriteComponent()->getSprite()->height(parameter_values[EMITTER].at(3));
	}
	else if (!drag)
	{
		particle_system->update(dt);
	}

	if (parameters == TEXTURE)
	{
		int y = 0;
		for (int i = 0; i < texturez.size(); i++)
		{
			texturez[i].spriteComponent()->getSprite()->yPos(ui_offset + y);
			y += texturez[i].spriteComponent()->getSprite()->height() + 5;
		}
	}
	else if (parameters == COLOURS)
	{
		int y = 0;
		for (int i = 0; i < num_of_colours; i++)
		{
			colours_ui[i]->spriteComponent()->getSprite()->yPos(ui_offset + y);
			y += colours_ui[i]->spriteComponent()->getSprite()->height() + 5;
		}
		int x = GAME_WIDTH / 2;
		for (int i = 0; i <= size_of_vector[COLOURS]; i++)
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
	setValues(1);

	return Scene::NONE;
}

void EditorScene::setValues(int value)
{
	switch (value)
	{
	case 0:
		parameter_values[DENSITY].at(0) = density;
		parameter_values[EMISSION_RATE].at(0) = emission_rate;
		parameter_values[DIMENSIONS].at(0) = particle_width;
		parameter_values[DIMENSIONS].at(1) = particle_height;
		parameter_values[ANGLES].at(0) = max_angle;
		parameter_values[ANGLES].at(1) = angle_offset;
		parameter_values[ANGLES].at(2) = randomise_angle;
		parameter_values[VELOCITY].at(0) = velocity;
		parameter_values[LIFETIME].at(0) = max_life_time;
		parameter_values[EMITTER].at(0) = emitter.x;
		parameter_values[EMITTER].at(1) = emitter.y;
		parameter_values[EMITTER].at(2) = emitter.length;
		parameter_values[EMITTER].at(3) = emitter.height;
		parameter_values[OPACITY].at(0) = target_opacity[0];
		parameter_values[OPACITY].at(1) = target_opacity[1];
		parameter_values[OPACITY].at(2) = target_opacity[2];
		parameter_values[OPACITY_RATE].at(0) = opacity_change_rate[0];
		parameter_values[OPACITY_RATE].at(1) = opacity_change_rate[1];
		parameter_values[COLOUR_RATE].at(0) = colour_change_rate[0];
		parameter_values[COLOUR_RATE].at(1) = colour_change_rate[1];
		parameter_values[COLOUR_RATE].at(2) = colour_change_rate[2];
		parameter_values[COLOUR_RATE].at(3) = colour_change_rate[3];
		break;
	case 1:
		density = parameter_values[DENSITY].at(0);
		emission_rate = parameter_values[EMISSION_RATE].at(0);
		particle_width = parameter_values[DIMENSIONS].at(0);
		particle_height = parameter_values[DIMENSIONS].at(1);
		max_angle = parameter_values[ANGLES].at(0);
		angle_offset = parameter_values[ANGLES].at(1);
		randomise_angle = parameter_values[ANGLES].at(2);
		velocity = parameter_values[VELOCITY].at(0);
		max_life_time = parameter_values[LIFETIME].at(0);
		emitter.x = parameter_values[EMITTER].at(0);
		emitter.y = parameter_values[EMITTER].at(1);
		emitter.length = parameter_values[EMITTER].at(2);
		emitter.height = parameter_values[EMITTER].at(3);
		target_opacity[0] = parameter_values[OPACITY].at(0);
		target_opacity[1] = parameter_values[OPACITY].at(1);
		target_opacity[2] = parameter_values[OPACITY].at(2);
		opacity_change_rate[0] = parameter_values[OPACITY_RATE].at(0);
		opacity_change_rate[1] = parameter_values[OPACITY_RATE].at(1);
		colour_change_rate[0] = parameter_values[COLOUR_RATE].at(0);
		colour_change_rate[1] = parameter_values[COLOUR_RATE].at(1);
		colour_change_rate[2] = parameter_values[COLOUR_RATE].at(2);
		colour_change_rate[3] = parameter_values[COLOUR_RATE].at(3);
		break;
	}
}

void EditorScene::render(ASGE::Renderer * renderer)
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	int w, h, m_a, a_o, r_a, v, l, e_x, e_y, e_l, e_h;
	w = particle_width;
	h = particle_height;
	m_a = max_angle;
	a_o = angle_offset;
	r_a = randomise_angle;
	v = velocity;
	l = max_life_time;
	e_x = emitter.x;
	e_y = emitter.y;
	e_l = emitter.length;
	e_h = emitter.height;
	if (drag || (debug == 2 || debug == 3))
	{
		emitter_point->render(renderer);
	}

	if (debug == 1 || debug == 3)
	{
		std::string line = "";
		line += "Particle Density: " + std::to_string(density);
		line += "\nEmission rate: " + std::to_string(emission_rate);
		line += "\nParticle Dimensions: " + std::to_string(w) + ", " + std::to_string(h);
		line += "\nMax Angle: " + std::to_string(max_angle);
		line += "\nAngle Offset: " + std::to_string(angle_offset);
		line += "\nRandomise Angle: " + std::to_string(r_a);
		line += "\nVelocity: " + std::to_string(v);
		line += "\nLifetime: " + std::to_string(l);
		line += "\nEmitter Position: " + std::to_string(e_x) + ", " + std::to_string(e_y);
		line += "\nEmitter Dimensions: " + std::to_string(e_l) + ", " + std::to_string(e_h);
		line += "\nOpacity Over Lifetime: " + std::to_string(target_opacity[0]) + ", " + std::to_string(target_opacity[1]) + ", " + std::to_string(target_opacity[2]);
		line += "\nOpacity Change Rate: " + std::to_string(opacity_change_rate[0]) + ", " + std::to_string(opacity_change_rate[1]);
		line += "\nColourChange Rate: " + std::to_string(colour_change_rate[0]) + ", " + std::to_string(colour_change_rate[1]) + ", " + std::to_string(colour_change_rate[2]) + ", " + std::to_string(colour_change_rate[3]);
		//line += "\nColour Over Lifetime: ";
		//for (int i = 0; i < 5; i++)
		//{
		//	line += displayColour(target_colour[i].r, target_colour[i].g, target_colour[i].b);
		//	if (i < 4)
		//	{
		//		line += ", ";
		//	}
		//}
		line += "\nTexture: " + texture_name;
		line += "\nFile Name: " + file_name;

		renderer->renderText(line, 0.0, 30.0, 1.0, ASGE::COLOURS::WHITE);
	}

	float x_pos = 1200.0;
	float y_pos = 30.0;
	for (int i = 0; i <= parameter_amount[1]; i++)
	{
		if (parameters < SAVE)
		{
			std::string line = parameter_names[parameters].at(i);
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
		//else if (parameters == SAVE)
		//{
		//	renderer->renderText("SAVE", x_pos, 30.0, 1.0, ASGE::COLOURS::WHITE);
		//}
		//else if (parameters == EXIT)
		//{
		//	renderer->renderText("EXIT", x_pos, 30.0, 1.0, ASGE::COLOURS::WHITE);
		//}
	}
	particle_system->render(renderer);



	if (parameters == COLOURS)
	{
		for (int i = 0; i < num_of_colours; i++)
		{
			colours_ui[i]->render(renderer);
		}
		for (int i = 0; i <= size_of_vector[COLOURS]; i++)
		{
			colours[i]->render(renderer);
		}
	}
	else if (parameters == TEXTURE)
	{
		for (int i = 0; i < texture_amount; i++)
		{
			texturez[i].render(renderer);
		}
	}
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].render(renderer);
		renderer->renderText(button_names[i], buttons[i].spriteComponent()->getSprite()->xPos(), buttons[i].spriteComponent()->getSprite()->yPos() + (buttons[i].spriteComponent()->getSprite()->height() * 0.75), 1.0, ASGE::COLOURS::BLACK);
	}

	if (update_system)
	{
		setValues(1);
		particle_system->updateParticleSystemValues(renderer,
			texture_name,
			density,
			emission_rate,
			particle_width, particle_height,
			max_angle, angle_offset, randomise_angle,
			velocity,
			max_life_time,
			emitter.x, emitter.y, emitter.length, emitter.height,
			target_opacity, opacity_change_rate,
			target_colour, colour_change_rate);
		update_system = false;
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
		else if (event->key == ASGE::KEYS::KEY_ENTER)
		{
			if (parameters == EXIT)
			{
				current_action = EditorScene::Action::CHANGE_TO_MENU;
			}
			//else if (parameters == SAVE)
			//{
			//	if (file_name != "")
			//	{
			//		FileSystem file;
			//		if (file.createFile(file_name,
			//			texture_name,
			//			density,
			//			emission_rate,
			//			particle_width, particle_height,
			//			max_angle, angle_offset, randomise_angle,
			//			velocity,
			//			max_life_time,
			//			emitter.x, emitter.y, emitter.length, emitter.height,
			//			target_opacity, opacity_change_rate,
			//			target_colour, colour_change_rate))
			//		{
			//
			//			current_action = EditorScene::Action::CHANGE_TO_MENU;
			//		}
			//	}
			//}
			else if (parameters < SAVE)
			{
				if (parameters < COLOURS)
				{
					if (parameters == ANGLES && parameter_amount[0] == 2) {
						if (user_input == "0" || user_input == "1") {
							parameter_values[parameters].at(parameter_amount[0]) = std::stof(user_input);
							update_system = true;
						}
					}
					else if (parameters == EMITTER && (parameter_amount[0] == 2 || parameter_amount[0] == 3)) {
						float value = std::stof(user_input);
						if (value > 1) {
							parameter_values[parameters].at(parameter_amount[0]) = std::stof(user_input);
							update_system = true;
						}
					}
					else if (parameters == OPACITY) {
						if (std::stof(user_input) <= 1.0f && std::stof(user_input) >= 0.0f) {
							parameter_values[parameters].at(parameter_amount[0]) = std::stof(user_input);
							update_system = true;
						}
					}
					else if (parameters == OPACITY_RATE) {
						if (std::stof(user_input) > 0.0f) {
							parameter_values[parameters].at(parameter_amount[0]) = std::stof(user_input);
							update_system = true;
						}
					}
					else {
						parameter_values[parameters].at(parameter_amount[0]) = std::stof(user_input);
						update_system = true;
					}
				}
				else if (parameters == FILENAME)
				{
					file_name = user_input;
				}
				user_input = "";
			}
		}
		if (event->key == ASGE::KEYS::KEY_UP || event->key == ASGE::KEYS::KEY_DOWN || event->key == ASGE::KEYS::KEY_LEFT || event->key == ASGE::KEYS::KEY_RIGHT) {
			if (event->key == ASGE::KEYS::KEY_RIGHT) {
				int x = parameters;
				x++;
				if (x > TEXTURE)
					x = DENSITY;

				parameter_amount[0] = 0;
				if (x < SAVE)
					parameter_amount[1] = size_of_vector[x];

				parameters = (Parameters)x;
			}
			else if (event->key == ASGE::KEYS::KEY_LEFT) {
				int x = parameters;
				x--;
				if (x < DENSITY)
					x = TEXTURE;

				parameter_amount[0] = 0;
				if (x < SAVE)
					parameter_amount[1] = size_of_vector[x];

				parameters = (Parameters)x;
			}
			else if (event->key == ASGE::KEYS::KEY_DOWN) {
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
		else if (parameters < SAVE)
		{
			if (parameters < COLOURS)
			{
				if (event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_PERIOD || event->key == ASGE::KEYS::KEY_MINUS)
				{
					if (user_input.size() < 10)
						user_input += event->key;
				}
			}
			else if (parameters >= COLOURS)
			{
				if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
				{
					user_input += "_";
				}
				else if (event->mods == 1 && event->key == ASGE::KEYS::KEY_EQUAL)
				{
					user_input += "+";
				}
				else if ((event->key >= ASGE::KEYS::KEY_SPACE && event->key <= ASGE::KEYS::KEY_BACKSLASH) && event->key != ASGE::KEYS::KEY_SLASH && event->key != ASGE::KEYS::KEY_LEFT_BRACKET)
				{
					if (user_input.size() < 15)
						user_input += event->key;
				}
			}
		}
	}
	if (event->action == ASGE::KEYS::KEY_REPEATED)
	{
		if (parameters < SAVE)
		{
			if (parameters < COLOURS)
			{
				if (event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_PERIOD || event->key == ASGE::KEYS::KEY_MINUS)
				{
					if (user_input.size() < 10)
						user_input += event->key;
				}
			}
			if (parameters >= COLOURS)
			{
				if (event->key >= ASGE::KEYS::KEY_A && event->key <= ASGE::KEYS::KEY_Z || event->key >= ASGE::KEYS::KEY_0 && event->key <= ASGE::KEYS::KEY_9 || event->key == ASGE::KEYS::KEY_MINUS)
				{
					if (user_input.size() < 15)
						user_input += event->key;
				}
				if (event->mods == 1 && event->key == ASGE::KEYS::KEY_MINUS)
				{
					user_input += "_";
				}
			}
			if (event->key == ASGE::KEYS::KEY_BACKSPACE)
			{
				if (user_input.size() > 0)
				{
					user_input.resize(user_input.size() - 1);
				}
			}
		}
	}
}

void EditorScene::clickHandler(const ASGE::ClickEvent * event)
{
	if (event->action != ASGE::KEYS::KEY_RELEASED)
	{
		if (event->button == ASGE::KEYS::LEFT_CLICK)
		{
			double x_pos, y_pos;
			input->getCursorPos(x_pos, y_pos);

			int check = 0;
			if (parameters == COLOURS)
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

				for (int i = 0; i <= size_of_vector[COLOURS]; i++)
				{
					if (colours[i]->spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
					{
						parameter_amount[0] = i;
						check = 1;
						break;
					}
				}
			}
			else if (parameters == TEXTURE)
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

			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i].spriteComponent()->getBoundingBox().isInside(x_pos, y_pos))
				{
					parameters = (Parameters)i;
					parameter_amount[0] = 0;
					//parameter_amount[1] = size_of_vector[parameters];
					ui_offset = 0;
					check = 1;
					if (i == SAVE)
					{
						if (file_name != "")
						{
							FileSystem file;
							if (file.createFile(file_name,
								texture_name,
								density,
								emission_rate,
								particle_width, particle_height,
								max_angle, angle_offset, randomise_angle,
								velocity,
								max_life_time,
								emitter.x, emitter.y, emitter.length, emitter.height,
								target_opacity, opacity_change_rate,
								target_colour, colour_change_rate))
							{
								parameters = DENSITY;
								current_action = EditorScene::Action::CHANGE_TO_MENU;
							}
						}
					}
					else if (i == EXIT)
					{
						parameters = DENSITY;
						file_name = "";
						current_action = EditorScene::Action::CHANGE_TO_MENU;
					}
					parameter_amount[1] = size_of_vector[parameters];
					break;
				}
			}

			if (check == 0)
			{

				x_dif = x_pos - parameter_values[EMITTER].at(0);
				y_dif = y_pos - parameter_values[EMITTER].at(1);
				drag = true;
			}
		}
	}
	if (event->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (event->button == ASGE::KEYS::LEFT_CLICK)
		{

			if (drag)
			{
				drag = false;
				update_system = true;
				//particle_system->updateParticleSystemValues(scene_ren,
				//	texture_name,
				//	density,
				//	particle_width, particle_height,
				//	max_angle, angle_offset, randomise_angle,
				//	velocity,
				//	max_life_time,
				//	emitter.x, emitter.y, emitter.length, emitter.height,
				//	target_opacity, opacity_change_rate,
				//	target_colour, colour_change_rate);
			}
		}
	}
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


std::string EditorScene::displayColour(float red, float green, float blue)
{
	if (red == ASGE::COLOURS::RED[0] && green == ASGE::COLOURS::RED[1] && blue == ASGE::COLOURS::RED[2])
	{
		return "Red";
	}
	else if (red == ASGE::COLOURS::BLUE[0] && green == ASGE::COLOURS::BLUE[1] && blue == ASGE::COLOURS::BLUE[2])
	{
		return "Blue";
	}
	else if (red == ASGE::COLOURS::GREEN[0] && green == ASGE::COLOURS::GREEN[1] && blue == ASGE::COLOURS::GREEN[2])
	{
		return "Green";
	}
	else if (red == ASGE::COLOURS::YELLOW[0] && green == ASGE::COLOURS::YELLOW[1] && blue == ASGE::COLOURS::YELLOW[2])
	{
		return "Yellow";
	}
	else if (red == ASGE::COLOURS::ORANGE[0] && green == ASGE::COLOURS::ORANGE[1] && blue == ASGE::COLOURS::ORANGE[2])
	{
		return "Orange";
	}
	else if (red == ASGE::COLOURS::LIGHTBLUE[0] && green == ASGE::COLOURS::LIGHTBLUE[1] && blue == ASGE::COLOURS::LIGHTBLUE[2])
	{
		return "Light Blue";
	}
	else
	{
		return "White";
	}
}

bool EditorScene::changeColour(std::string colour, int para)
{
	if (colour == "RED")
	{
		target_colour[para] = ASGE::COLOURS::RED;
		return true;
	}
	else if (colour == "BLUE")
	{
		target_colour[para] = ASGE::COLOURS::BLUE;
		return true;
	}
	else if (colour == "GREEN")
	{
		target_colour[para] = ASGE::COLOURS::GREEN;
		return true;
	}
	else if (colour == "GREY")
	{
		target_colour[para] = ASGE::COLOURS::GREY;
		return true;
	}
	else if (colour == "YELLOW")
	{
		target_colour[para] = ASGE::COLOURS::YELLOW;
		return true;
	}
	else if (colour == "ORANGE")
	{
		target_colour[para] = ASGE::COLOURS::ORANGE;
		return true;
	}
	else if (colour == "WHITE")
	{
		target_colour[para] = ASGE::COLOURS::WHITE;
		return true;
	}
	else if (colour == "LIGHT BLUE")
	{
		target_colour[para] = ASGE::COLOURS::LIGHTBLUE;
		return true;
	}
	return false;
}
