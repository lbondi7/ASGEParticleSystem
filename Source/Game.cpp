#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "GameScene.h"
#include "MenuScene.h"
#include "EditorScene.h"
#include "SimulationScene.h"
#include "Game.h"

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
AngryBirdsGame::~AngryBirdsGame()
{
	inputs->unregisterCallback(key_handler_id);
	inputs->unregisterCallback(click_handler_id);
	inputs->unregisterCallback(scroll_handler_id);
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The keyHandler and clickHandler
			 callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool AngryBirdsGame::init()
{
	game_height = 1080;
	game_width = 1920;

	if (!initAPI())
	{
		return false;
	}

	key_handler_id = inputs->addCallbackFnc(ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);
	click_handler_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);
	scroll_handler_id = inputs->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &AngryBirdsGame::scrollHandler, this);

	//toggleFPS();
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	inputs->use_threads = false;

	{
		FileSystem file;
		file.getTxtFileContent("particleNames");
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			file_names.push_back(file.retrieveContent(i));
		}
	}

	scenes.push_back(std::unique_ptr<MenuScene>(new MenuScene));
	scenes.push_back(std::unique_ptr<SimulationScene>(new SimulationScene));
	scenes.push_back(std::unique_ptr<GameScene>(new GameScene));
	scenes.push_back(std::unique_ptr<EditorScene>(new EditorScene));

	for (int i = 0; i < scenes.size(); ++i) {
		if (!scenes[i]->init(renderer.get(), inputs.get(), file_names))
			return false;
	}


	return true;
}

void AngryBirdsGame::update(const ASGE::GameTime& us)
{
	auto dt_sec = us.delta_time.count() / 1000.0;
	switch (scenes[current_scene]->update(dt_sec))
	{
	case Scene::MENU_SIM: {
		if (current_scene == CurrentScene::MENU_SCENE)
		{
			current_scene = CurrentScene::SIM_SCENE;
		}
		else if (current_scene == CurrentScene::SIM_SCENE)
		{
			current_scene = CurrentScene::MENU_SCENE;
		}
		break;
	}
	case Scene::MENU_GAME: {
		if (current_scene == CurrentScene::MENU_SCENE)
		{
			current_scene = CurrentScene::GAME_SCENE;
		}
		else if (current_scene == CurrentScene::GAME_SCENE)
		{
			current_scene = CurrentScene::MENU_SCENE;
		}
		break;
	}
	case Scene::MENU_EDITOR: {
		if (current_scene == CurrentScene::MENU_SCENE)
		{
			current_scene = CurrentScene::EDITOR_SCENE;
		}
		else if (current_scene == CurrentScene::EDITOR_SCENE)
		{
			if (scenes[current_scene]->addFilename() != "")
			{
				file_names.push_back(scenes[current_scene]->addFilename());
				FileSystem file;
				file.editFile(file_names);
			}
			current_scene = CurrentScene::MENU_SCENE;
		}
		break;
	}
	case Scene::RESET_SCENES: {

		for (int i = 0; i < scenes.size(); i++)
		{
			scenes[i].reset();
		}
		scenes[0] = std::unique_ptr<MenuScene>(new MenuScene);
		scenes[1] = std::unique_ptr<SimulationScene>(new SimulationScene);
		scenes[2] = std::unique_ptr<GameScene>(new GameScene);
		scenes[3] = std::unique_ptr<EditorScene>(new EditorScene);
		for (int i = 0; i < scenes.size(); i++)
		{
			if (!scenes[i]->init(renderer.get(), inputs.get(), file_names))
				signalExit();
		}

		file_names.clear();
		FileSystem file;
		file.getTxtFileContent("particleNames");
		for (int i = 0; i < file.retrieveContentSize(); i++)
		{
			file_names.push_back(file.retrieveContent(i));
		}

		break;
	}
	case Scene::EXIT_SOFTWARE: {
		signalExit();
		break;
	}
	case Scene::NONE:
	{
		break;
	}
	}
}

void AngryBirdsGame::render(const ASGE::GameTime& us)
{
	renderer->setFont(0);

	scenes[current_scene]->render(renderer.get());
}

void AngryBirdsGame::keyHandler(const ASGE::SharedEventData data) {

	auto event = static_cast<const ASGE::KeyEvent *>(data.get());
	scenes[current_scene]->keyHandler(event);

}

void AngryBirdsGame::clickHandler(const ASGE::SharedEventData data) {

	auto event = static_cast<const ASGE::ClickEvent *>(data.get());
	scenes[current_scene]->clickHandler(event);
}

void AngryBirdsGame::scrollHandler(const ASGE::SharedEventData data) {

	auto event = static_cast<const ASGE::ScrollEvent *>(data.get());
	scenes[current_scene]->scrollHandler(event);
}