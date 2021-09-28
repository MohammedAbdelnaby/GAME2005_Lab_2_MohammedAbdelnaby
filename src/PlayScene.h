#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	Label* m_pInstructionsLabel{};
	glm::vec2 m_mousePosition;
	Target* m_ball;
	int StartingX = 100;
	int StartingY = 500;
	int LaunchElevationAngle = -60;
	float LaunchSpeed = 10;
	float AccelerationGravity = -9;
	float m_time = 0;

	float vx;
	float vy;

	// UI Items

};

#endif /* defined (__PLAY_SCENE__) */