#include "SpaceGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Engine.h"
#include "Game/GameData.h"

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>(this);

    m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "Righteous-Regular.ttf", 48));
	m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Righteous-Regular.ttf", 48));
	m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Righteous-Regular.ttf", 48));
	
    return true;
}

void SpaceGame::Update(float dt) {
    switch (m_gameState) {
    case SpaceGame::GameState::Initializee:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound: {
        //std::shared_ptr<viper::Model> playerM = std::make_shared < viper::Model>(GameData::playerPoints, vec3{ 0, 0, 255 });
        viper::Transform transform{ vec2{600 , 512}, 0, 1.5f };
        auto player = std::make_unique<Player>(transform, viper::Resources().Get<viper::Texture>("red_02.png", viper::GetEngine().GetRenderer()));
        player->damping = 0.5f;
        player->name = "Player";
        player->tag = "Player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f) {
            m_enemySpawnTimer = 4;
			SpawnEnemy();
        }
        break;
    case SpaceGame::GameState::PlayerDead:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0.0f) {
            m_lives--;
            m_scene->RemoveAllActors();
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
				m_stateTimer = 3.0f;
            } else m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_gameState = GameState::Title;
			m_scene->RemoveAllActors();
		}
        break;
    default:
        break;
    }

	m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {
    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "Asteroids", vec3{ 255, 255, 0 });
        m_titleText->Draw(renderer, 500, 400);
    }
    if (m_gameState == GameState::GameOver) {
		m_titleText->Create(renderer, "Game Over", vec3{ 255, 0, 0 });
		m_titleText->Draw(renderer, 500, 400);
    }

	m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), vec3{ 255, 255, 255 });
	m_scoreText->Draw(renderer, 20, 20);

	m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), vec3{ 255, 255, 255 });
	m_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), 20.0f);
    
    m_scene->Draw(renderer);

	viper::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::Shutdown() {
	m_scene.reset();
}

void SpaceGame::SpawnEnemy() {
    viper::Transform transform{ vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 }, 0, 3 };
    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, viper::Resources().Get<viper::Texture>("Rock_1.png", viper::GetEngine().GetRenderer()));
    enemy->damping = 1.0f;
    enemy->speed = 400;
    enemy->tag = "enemy";
    m_scene->AddActor(std::move(enemy));
}

void SpaceGame::OnPlayerDeath() {
	m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f;
}
