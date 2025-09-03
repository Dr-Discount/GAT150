#include "Game/Player.h"
#include "SpaceGame.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <ranges>

void Json();

int main(int argc, char* argv[]) {
    viper::SetCurrentDirectory("Assets");

	std::cout << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        viper::Logger::Debug("Arg {}: {}", i, argv[i]);
    }

	std::fstream stream("text.txt");
    if (!stream) {
		viper::Logger::Error("Failed to open file: test.txt");
    }
    std::string line;
    while (std::getline(stream, line)) {
		std::cout << line << std::endl;
	}

    std::string vstr("{ 23.4, 76.3 }");
	std::stringstream sstream(vstr);
	vec2 v;
	sstream >> v;
	std::cout << v << std::endl;

    Json();

    return 0;

	viper::GetEngine().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

    SDL_Event e;
    bool quit = false;

    std::vector<vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(vec2{ static_cast<float>(viper::random::getInt(0, 1280)), static_cast<float>(viper::random::getInt(0, 1024)) });  
	}

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
        viper::GetEngine().Update();
		game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //float lenght = starSpeed.Length();

        if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor((float)color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		viper::GetEngine().GetRenderer().DrawTexture(background.get(), 800, 900, 0, 1.0f);
        
        /*for (auto& star : stars) {
			star = star += starSpeed * viper::GetEngine().GetTime().GetDeltaTime();

			if (star.x > 1280) star.x = 0;
			if (star.x < 0) star.x = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(0, 255), viper::random::getInt(0, 255), viper::random::getInt(0, 255), 255);
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }*/

		game->Draw(viper::GetEngine().GetRenderer());

		rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
        
        viper::GetEngine().GetRenderer().Present();
    }
    viper::GetEngine().Shutdown();

    return 0;
}

void Json() {
    viper::SetCurrentDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    viper::ReadTextFile("json.txt", buffer);
	std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    viper::Load("json.txt", document);

    // read the age data from the json
    std::string name;
    int age;
    float speed;
    bool isAwake;
    vec2 position;
    vec3 color;

    // read the json data
    viper::Read(document, "name", name);
    viper::Read(document, "age", age);
    viper::Read(document, "speed", speed);
    viper::Read(document, "isAwake", isAwake);
    viper::Read(document, "position", position);
    viper::Read(document, "color", color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
    
}