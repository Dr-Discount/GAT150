#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "engine.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Game/Player.h"
#include "SpaceGame.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Core/File.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <ranges>

int main(int argc, char* argv[]) {
    viper::SetCurrentDirectory("Assets");

	//initialize game
	viper::GetEngine().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

	//viper::Actor actor{ transform, arrow };

    SDL_Event e;
    bool quit = false;

    std::vector<vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(vec2{ static_cast<float>(viper::random::getInt(0, 1280)), static_cast<float>(viper::random::getInt(0, 1024)) });  
	}

    //std::vector<vec2> points;

    //audio
    viper::GetEngine().GetAudioSystem().AddSound("test.wav", "test");
    viper::GetEngine().GetAudioSystem().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudioSystem().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudioSystem().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudioSystem().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudioSystem().AddSound("open-hat.wav", "open-hat");


    while (!quit) {
        viper::GetEngine().Update();
		game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor((float)color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		game->Draw(viper::GetEngine().GetRenderer());

        vec2 starSpeed{ 50.0f, 0 };
		float lenght = starSpeed.Length();

        for (auto& star : stars) {
			star = star += starSpeed * viper::GetEngine().GetTime().GetDeltaTime();

			if (star.x > 1280) star.x = 0;
			if (star.x < 0) star.x = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(0, 255), viper::random::getInt(0, 255), viper::random::getInt(0, 255), 255);
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }
        viper::GetEngine().GetRenderer().Present();
    }
    viper::GetEngine().Shutdown();

    return 0;
}