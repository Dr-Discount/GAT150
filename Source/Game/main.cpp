#include "Game/Player.h"
#include "SpaceGame.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <ranges>

int main(int argc, char* argv[]) {
    viper::SetCurrentDirectory("Assets");

	viper::GetEngine().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

    SDL_Event e;
    bool quit = false;

    //audio
    viper::GetEngine().GetAudioSystem().AddSound("test.wav", "test");
    viper::GetEngine().GetAudioSystem().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudioSystem().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudioSystem().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudioSystem().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudioSystem().AddSound("open-hat.wav", "open-hat");

	auto kermit = viper::Resources().Get<viper::Texture>("red_02.png", viper::GetEngine().GetRenderer());
	auto background = viper::Resources().Get<viper::Texture>("Space.png", viper::GetEngine().GetRenderer());

    float rotate = 0;
    vec2 starSpeed{ 50.0f, 0 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        viper::GetEngine().Update();
		game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        vec3 color{ 0, 0, 0 };
        viper::GetEngine().GetRenderer().SetColor((float)color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		game->Draw(viper::GetEngine().GetRenderer());

		rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
        
        viper::GetEngine().GetRenderer().Present();
    }
    viper::GetEngine().Shutdown();

    return 0;
}