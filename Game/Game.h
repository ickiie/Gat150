#pragma once
#include "Engine.h"

class Game {

public:
	enum class eState {

		Reset,
		Title,
		LevelText,
		StartGame,
		StartLevel,
		Level,
		LevelComplete,
		Levelv2Text,
		Prep,
		StartLevelv2,
		Levelv2,
		Levelv2Complete,
		PlayerDead,
		GameOver

	};


public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return false; }
	bool checkQuit();

private:
	void Reset();
	void Title();
	void LevelText();
	void StartGame();
	void StartLevel();
	void Level();
	void LevelComplete();
	void Levelv2Text();
	void Prep();
	void StartLevelv2();
	void Levelv2();
	void Levelv2Complete();
	void PlayerDead();
	void GameOver();

	void OnAddScore(const nc::Event& event);

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;
	
private:
	bool quit = false;

	eState state = eState::Reset;
	int score = 0;
	float stateTimer = 0;
	float spawnTimer = 0;
	float currentLevelTime{ 0 };
	float overallTime = 0;
	float randomTimer = 0;

};

