#include "MenuScene.h"

MenuScene::~MenuScene()
{
}

bool MenuScene::init(ASGE::Renderer * renderer, ASGE::Input* input, std::vector<std::string> file_names)
{
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	return true;
}

Scene::NextScene MenuScene::update(float dt)
{
	if (current_action == MenuScene::Action::CHANGE_TO_SIM)
	{
		current_action = MenuScene::Action::NONE;
		return Scene::MENU_SIM;
	}
	else if (current_action == MenuScene::Action::CHANGE_TO_GAME)
	{
		current_action = MenuScene::Action::NONE;
		return Scene::MENU_GAME;
	}
	else if (current_action == MenuScene::Action::CHANGE_TO_EDITOR)
	{
		current_action = MenuScene::Action::NONE;
		return Scene::MENU_EDITOR;
	}
	else if (current_action == MenuScene::Action::RESET_SOFTWARE)
	{
		return Scene::RESET_SCENES;
	}
	else if (current_action == MenuScene::Action::EXIT)
	{
		return Scene::EXIT_SOFTWARE;
	}

	return Scene::NONE;
}

void MenuScene::render(ASGE::Renderer * renderer)
{
	renderer->setClearColour(ASGE::COLOURS::BLUE);
	renderer->renderText(menu == Action::CHANGE_TO_SIM ? "SIM<-" : "SIM", 5, GAME_HEIGHT * 0.05, 1.0, ASGE::COLOURS::ANTIQUEWHITE);
	renderer->renderText(menu == Action::CHANGE_TO_GAME ? "GAME<-" : "GAME", 5, GAME_HEIGHT * 0.07, 1.0, ASGE::COLOURS::ANTIQUEWHITE);
	renderer->renderText(menu == Action::CHANGE_TO_EDITOR ? "EDITOR<-" : "EDITOR", 5, GAME_HEIGHT * 0.09, 1.0, ASGE::COLOURS::ANTIQUEWHITE);
	renderer->renderText(menu == Action::EXIT ? "EXIT<-" : "EXIT", 5, GAME_HEIGHT * 0.11, 1.0, ASGE::COLOURS::ANTIQUEWHITE);
}

std::string MenuScene::addFilename()
{
	return std::string();
}

void MenuScene::keyHandler(const ASGE::KeyEvent * event)
{
	if (event->action == ASGE::KEYS::KEY_PRESSED)
	{
		if (event->key == ASGE::KEYS::KEY_ENTER)
		{
			if (menu == MenuScene::Action::CHANGE_TO_SIM)
				current_action = MenuScene::Action::CHANGE_TO_SIM;
			else if (menu == MenuScene::Action::CHANGE_TO_GAME)
				current_action = MenuScene::Action::CHANGE_TO_GAME;
			else if (menu == MenuScene::Action::CHANGE_TO_EDITOR)
				current_action = MenuScene::Action::CHANGE_TO_EDITOR;
			else if (menu == MenuScene::Action::EXIT)
				current_action = MenuScene::Action::EXIT;
		}
		else if (event->key == ASGE::KEYS::KEY_R)
		{
			current_action = MenuScene::Action::RESET_SOFTWARE;
		}
		else if (event->key == ASGE::KEYS::KEY_ESCAPE)
		{
			current_action = MenuScene::Action::EXIT;
		}
		else if (event->key == ASGE::KEYS::KEY_DOWN)
		{
			menu++;
			if (menu > MenuScene::Action::EXIT)
				menu = MenuScene::Action::CHANGE_TO_SIM;
		}
		else if (event->key == ASGE::KEYS::KEY_UP)
		{
			menu--;
			if (menu < MenuScene::Action::CHANGE_TO_SIM)
				menu = MenuScene::Action::EXIT;
		}

	}
}

void MenuScene::clickHandler(const ASGE::ClickEvent * event)
{
}

void MenuScene::scrollHandler(const ASGE::ScrollEvent * event)
{
}
