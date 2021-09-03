#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"


void Game::Initialize() {

	// create engine
	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	//register classes
	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

	// create scene
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../Resources");

	//events
	engine->Get<nc::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
	// player death


	

	// actors
	/*std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(nc::Transform{ { 400, 300 }, 0, 1 });
	{
		nc::SpriteComponent* component = actor->AddComponent<nc::SpriteComponent>();
		component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("animations/character.png", engine->Get<nc::Renderer>());
	}*/
	/*{
		nc::PhysicsComponent* component = actor->AddComponent<nc::PhysicsComponent>();
		component->ApplyForce(nc::Vector2::right * 200);
	}*/
	//std::unique_ptr<nc::Actor> actor = std::make_unique <nc::Actor>(nc::Transform{ nc::Vector2{400, 300}, 0, 1 });
	//{
	//	auto component = nc::ObjectFactory::Instance().Create<nc::SpriteAnimationComponent>("SpriteAnimationComponent");

	//	//nc::SpriteAnimationComponent* component = actor->AddComponent<nc::SpriteAnimationComponent>();
	//	component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("animations/sparkle.png", engine->Get<nc::Renderer>());
	//	component->fps = 12;
	//	component->numFramesX = 8;
	//	component->numFramesY = 8;
	//	actor->AddComponent(std::move(component));
	//}

	//scene->AddActor(std::move(actor));
}

void Game::Shutdown() {

	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update() {

	engine->Update();
	
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Held) {

		quit = true;
	}

	switch (state)
	{
	case Game::eState::Reset:
		Reset();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::LevelText:
		LevelText();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::LevelComplete:
		LevelComplete();
		break;
	case Game::eState::Levelv2Text:
		Levelv2Text();
		break;
	case Game::eState::Prep:
		Prep();
		break;
	case Game::eState::StartLevelv2:
		StartLevelv2();
		break;
	case Game::eState::Levelv2:
		Levelv2();
		break;
	case Game::eState::Levelv2Complete:
		Levelv2Complete();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	//update score
	auto scoreActor = scene->FindActor("Score");
	if (scoreActor) {
		scoreActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(score));
	}
	//update Time
	auto timeActor = scene->FindActor("Time");
	if (timeActor) {
		timeActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(currentLevelTime));
	}
	
	scene->Update(engine->time.deltaTime);
}

void Game::Draw() {

	engine->Get<nc::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}

bool Game::checkQuit()
{
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Held) {
		return true;
		}
	else
	{
		return false;
	}
 
}

void Game::Reset() {

	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = nc::json::Load("title.txt", document);
	nc::json::Load("title.txt", document);

	scene->Read(document);

	state = eState::Title;
}

void Game::Title()
{
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {

		auto title = scene->FindActor("Title");
		assert(title);
		title->active = false;

		rapidjson::Document document;
		bool success = nc::json::Load("leveltext.txt", document);
		nc::json::Load("leveltext.txt", document);

		scene->Read(document);

		state = eState::LevelText;
	}
}

void Game::LevelText()
{
	randomTimer += engine->time.deltaTime;


	if (randomTimer >= 2) {
		auto instruct = scene->FindActor("Instruct");
		instruct->active = true;
	}

	if (randomTimer >= 3) {
		auto instruct2 = scene->FindActor("Instructb");
		instruct2->active = true;
	}

	if (randomTimer >= 4) {
		auto instruct3 = scene->FindActor("Instructc");
		instruct3->active = true;
	}

	if (randomTimer >= 4 && engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {
		auto instruct = scene->FindActor("Instruct");
		instruct->active = false;
		auto instruct2 = scene->FindActor("Instructb");
		instruct2->active = false;
		auto instruct3 = scene->FindActor("Instructc");
		instruct3->active = false;
		
		state = eState::StartGame;
	}

}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = nc::json::Load("scene.txt", document);
	nc::json::Load("scene.txt", document);

	scene->Read(document);

	nc::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = nc::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1) {

		auto player = nc::ObjectFactory::Instance().Create<nc::Actor>("Player");
		player->transform.position = nc::Vector2{ 400, 350 };
		scene->AddActor(std::move(player));

		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	currentLevelTime += engine->time.deltaTime;
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0) {

		spawnTimer = nc::RandomRange(2, 4);

		auto coin = nc::ObjectFactory::Instance().Create<nc::Actor>("Coin");
		coin->transform.position = nc::Vector2{ nc::RandomRange(100, 700), 150.0f };
		scene->AddActor(std::move(coin));
	}

	if (score >= 5) {

		auto enemy = scene->FindActor("Enemy");
		enemy->active = true;
	}
	if (score >= 10) {
		rapidjson::Document document;
		bool success = nc::json::Load("levelComplete.txt", document);
		nc::json::Load("levelComplete.txt", document);

		scene->Read(document);

		randomTimer = 0;

		state = eState::LevelComplete;
	}
}

void Game::LevelComplete()
{
	
	randomTimer += engine->time.deltaTime;

	auto enemy = scene->FindActor("Enemy");
	enemy->destroy = true;
	auto player = scene->FindActor("Player");
	player->destroy = true;

	auto timeActor = scene->FindActor("Infob");
	if (timeActor) {
		timeActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(currentLevelTime));
	}

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {

		overallTime += currentLevelTime;

		auto text = scene->FindActor("Congrat");
		text->destroy = true;
		auto text2 = scene->FindActor("Info");
		text2->destroy = true;
		auto text3 = scene->FindActor("Infob");
		text3->destroy = true;
		auto text4 = scene->FindActor("Infoc");
		text4->destroy = true;

		rapidjson::Document document;
		bool success = nc::json::Load("levelv2text.txt", document);
		nc::json::Load("levelv2text.txt", document);

		scene->Read(document);

		randomTimer = 0;

		state = eState::Levelv2Text;
	}
}

void Game::Levelv2Text()
{
	randomTimer += engine->time.deltaTime;
	
	if (randomTimer >= 1) {
		auto instruct = scene->FindActor("Instructy");
		instruct->active = true;
	}

	if (randomTimer >= 2 && engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {

		randomTimer = 0;
		state = eState::Prep;
	}

}

void Game::Prep()
{
	for (int i = 0; i < 30; i++) {

		auto block = scene->FindActor("tile01");
		block->destroy = true;
		auto block2 = scene->FindActor("tile02");
		block2->destroy = true;
		auto block3 = scene->FindActor("tile03");
		block3->destroy = true;
		auto block4 = scene->FindActor("tile04");
		block4->destroy = true;
	}

	auto text = scene->FindActor("Instructy");
	text->destroy = true;

	rapidjson::Document document;
	bool success = nc::json::Load("scene.txt", document);
	nc::json::Load("scene.txt", document);

	scene->Read(document);

	nc::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = nc::json::Load("mapv2.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevelv2;
	stateTimer = 0;
}

void Game::StartLevelv2()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1) {

		auto player = nc::ObjectFactory::Instance().Create<nc::Actor>("Player");
		player->transform.position = nc::Vector2{ 400, 450 };
		scene->AddActor(std::move(player));

		spawnTimer = 2;
		currentLevelTime = 0;
		score = 0;
		state = eState::Levelv2;
	}
}

void Game::Levelv2()
{
	currentLevelTime += engine->time.deltaTime;
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer <= 0) {

		spawnTimer = nc::RandomRange(0, 6);

		auto coin = nc::ObjectFactory::Instance().Create<nc::Actor>("Coin");
		coin->transform.position = nc::Vector2{ nc::RandomRange(50, 750), 100.0f };
		scene->AddActor(std::move(coin));

	}

	if (score >= 1) {

		auto enemy = scene->FindActor("Enemy3");
		enemy->active = true;
	}
	if (score >= 5) {

		auto enemy2 = scene->FindActor("Enemy2");
		enemy2->active = true;
	}
	if (score >= 10) {
		rapidjson::Document document;
		bool success = nc::json::Load("levelCompletev2.txt", document);
		nc::json::Load("levelCompletev2.txt", document);

		scene->Read(document);

		randomTimer = 0;

		state = eState::Levelv2Complete;
	}
}

void Game::Levelv2Complete()
{
	randomTimer += engine->time.deltaTime;

	auto enemy = scene->FindActor("Enemy");
	enemy->destroy = true;
	auto enemy2 = scene->FindActor("Enemy2");
	enemy2->destroy = true;
	auto player = scene->FindActor("Player");
	player->destroy = true;

	auto timeActor = scene->FindActor("Infob");
	if (timeActor) {
		timeActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(currentLevelTime));
	}

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {

		overallTime += currentLevelTime;

		auto text = scene->FindActor("Congrat");
		text->destroy = true;
		auto text2 = scene->FindActor("Info");
		text2->destroy = true;
		auto text3 = scene->FindActor("Infob");
		text3->destroy = true;
		auto text4 = scene->FindActor("Infoc");
		text4->destroy = true;

		rapidjson::Document document;
		bool success = nc::json::Load("gameover.txt", document);
		nc::json::Load("gameover.txt", document);

		scene->Read(document);

		randomTimer = 0;

		state = eState::GameOver;
	}
}

void Game::PlayerDead()
{
}

void Game::GameOver()
{
	//update final time
	auto timeActorE = scene->FindActor("ETime");
	if (timeActorE) {
		timeActorE->GetComponent<nc::TextComponent>()->SetText(std::to_string(overallTime) + "seconds to beat Coin Collector.");
	}


	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held) {

		quit = true;
	}
}

void Game::OnAddScore(const nc::Event& event) {

	score += std::get<int>(event.data);
}
