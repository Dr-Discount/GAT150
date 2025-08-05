#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public viper::Game {
public:
	enum GameState {
		Initializee,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver
	};

public:
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(viper::Renderer& renderer) override;
	void Shutdown() override;

	void OnPlayerDeath();
private:
	GameState m_gameState = GameState::Initializee;
	float m_enemySpawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	std::shared_ptr<viper::Font> m_titleFont;
	std::shared_ptr<viper::Font> m_uiFont;

	std::unique_ptr<viper::Text> m_titleText;
	std::unique_ptr<viper::Text> m_scoreText;
	std::unique_ptr<viper::Text> m_livesText;
};