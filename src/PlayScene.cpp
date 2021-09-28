#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <cmath>

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLineF(Renderer::Instance().getRenderer(), StartingX, StartingY, StartingX + (cos((LaunchElevationAngle * (3.14 / 180)))) *100
		, StartingY + (sin((LaunchElevationAngle * (3.14 / 180))))* 100);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{

	float dt = Game::Instance().getDeltaTime();
	m_time += dt;
	updateDisplayList();
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		vx = (cos((LaunchElevationAngle * (3.14 / 180))) * LaunchSpeed);
		vy = (sin((LaunchElevationAngle * (3.14 / 180))) * LaunchSpeed) - (AccelerationGravity * m_time);
		m_ball->getTransform()->position.y += vy;
		m_ball->getTransform()->position.x += vx; 
	}
	else
	{
		m_time = 0;
		m_ball->getTransform()->position = glm::vec2(StartingX, StartingY);
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();




	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	m_ball = new Target();
	m_ball->getTransform()->position = glm::vec2(StartingX, StartingY);
	addChild(m_ball);
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pInstructionsLabel = new Label("Hold Space to throw, Realse to reset", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);


	ImGui::SliderInt("X", &StartingX, 50, 300, "%.3f");

	ImGui::SliderInt("Y", &StartingY, 50, 300, "%.3f");

	ImGui::SliderInt("Angle", &LaunchElevationAngle, 0, -360, "%.3f");

	ImGui::SliderFloat("Speed", &LaunchSpeed, 0.0f, 50.0f, "%.3f");

	ImGui::SliderFloat("Gravity", &AccelerationGravity, 0.0f, -50.0f, "%.3f");

	
	ImGui::End();
}
