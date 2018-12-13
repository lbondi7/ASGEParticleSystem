#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "Scene.h"


/**
*  An OpenGL Game based on ASGE.
*/
class AngryBirdsGame :
	public ASGE::OGLGame
{
public:
	AngryBirdsGame() = default;
	~AngryBirdsGame();

	virtual bool init() override;
	virtual void update(const ASGE::GameTime& us) override;
	virtual void render(const ASGE::GameTime& us) override;


private:
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void scrollHandler(const ASGE::SharedEventData data);

	int key_handler_id = -1;
	int click_handler_id = -1;
	int scroll_handler_id = -1;

	std::vector<std::unique_ptr<Scene>> scenes;


	enum CurrentScene {

		MENU_SCENE = 0,
		SIM_SCENE = 1,
		GAME_SCENE = 2,
		EDITOR_SCENE = 3
	};

	CurrentScene current_scene = CurrentScene::MENU_SCENE;
	std::vector<std::string> file_names;
};
