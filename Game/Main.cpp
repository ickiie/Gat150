#include "Game.h"

//define macro
#define PRINT(str) std::cout << str << std::endl;

int main(int, char**)
{

	//call macro
	PRINT("macro")

	Game game;
	game.Initialize();




	/*rapidjson::Document document;
	bool success = nc::json::Load("json.txt", document);
	assert(success);

	std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;*/


	bool quit = false;
	SDL_Event event;
	//float quitTime = engine.time.time + 5.0f;

	if (game.scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Held) {

		quit = true;
	}
	
	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		if (game.checkQuit() == true) {
			quit = true;
		}



		game.Update();
		game.Draw();
				
	}

	SDL_Quit();

	return 0;
}
