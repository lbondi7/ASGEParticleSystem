#pragma once
#include "Scene.h"
#include "GameObject.h"

class MenuScene :
	public Scene
{
public:
	MenuScene() = default;
	virtual ~MenuScene();

	virtual bool init(ASGE::Renderer* renderer, ASGE::Input* input, std::vector<std::string> file_names) override;
	virtual Scene::NextScene update(float dt) override;
	virtual void render(ASGE::Renderer* renderer) override;
	virtual std::string addFilename() override;
	virtual void keyHandler(const ASGE::KeyEvent* event) override;
	virtual void clickHandler(const ASGE::ClickEvent* event) override;
	virtual void scrollHandler(const ASGE::ScrollEvent* event) override;

private:

	enum Action
	{
		CHANGE_TO_SIM = 0,
		CHANGE_TO_GAME = 1,
		CHANGE_TO_EDITOR = 2,
		EXIT = 3,
		RESET_SOFTWARE = 4,
		NONE = 5
	};

	Action current_action = NONE;

	int menu = 0;
};