#pragma once
#include <Engine\OGLGame.h>

class Scene
{
public:
	enum NextScene
	{
		MENU_SIM = 0,
		MENU_GAME = 1,
		MENU_EDITOR = 2,
		RESET_SCENES = 3,
		EXIT_SOFTWARE = 4,
		NONE = 5
	};

	Scene() = default;
	virtual ~Scene() = default;

	virtual bool init(ASGE::Renderer* renderer, ASGE::Input* input, std::vector<std::string> file_names) = 0;
	virtual NextScene update(float dt) = 0;
	virtual void render(ASGE::Renderer* renderer) = 0;
	virtual std::string addFilename() = 0;
	virtual void keyHandler(const ASGE::KeyEvent* event) = 0;
	virtual void clickHandler(const ASGE::ClickEvent* event) = 0;
	virtual void scrollHandler(const ASGE::ScrollEvent* event) = 0;
};