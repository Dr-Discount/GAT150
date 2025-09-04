#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public viper::Game, public viper::Observer {
public:
	enum GameState {
		Initializee,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameWon,
		GameOver
	};

public:
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(viper::Renderer& renderer) override;
	void Shutdown() override;
	void OnNotify(const viper::Event& event) override;

	void OnPlayerDeath();
	void SpawnEnemy();
private:
	GameState m_gameState = GameState::Initializee;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	std::unique_ptr<viper::Text> m_titleText;
	std::unique_ptr<viper::Text> m_scoreText;
	std::unique_ptr<viper::Text> m_livesText;
};